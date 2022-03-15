/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_redirects_array.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:35:25 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/14 19:32:11 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_get_filename(char *line, int i[5])
{
	while (line[++i[0]] && line[i[0]] == ' ')
		;
	while (line[i[0] + i[1]] && !ft_strchr(" <>", line[i[0] + i[1]]))
	{
		ft_check_quotes(line[i[0] + i[1]], &i[3], &i[4]);
		if (i[3] || i[4])
		{
			while (i[3] || i[4])
			{
				i[1]++;
				ft_check_quotes(line[i[0] + i[1]], &i[3], &i[4]);
			}
		}
		i[1]++;
	}
	return (ft_substr(line, i[0], i[1]));
}

static t_redirs	**ft_init_redirects(char *line)
{
	int			i;
	int			redirs;
	t_redirs	**redirs_arr;
	int			inside_s_quote;
	int			inside_d_quote;

	i = -1;
	redirs = 1;
	redirs_arr = NULL;
	inside_s_quote = 0;
	inside_d_quote = 0;
	while (line[++i])
	{
		ft_check_quotes(line[i], &inside_s_quote, &inside_d_quote);
		if (!inside_d_quote && !inside_s_quote
			&& ft_strchr("<>", line[i]) && redirs++)
			if (ft_strchr("<>", line[i + 1]))
				i++;
	}
	redirs_arr = (t_redirs **)malloc(sizeof(t_redirs *) * redirs);
	if (!redirs_arr)
		fatal_error(MLC_ERROR);
	ft_memset(redirs_arr, 0, sizeof(t_redirs) * redirs);
	return (redirs_arr);
}

static int	ft_get_redirect_mode(char *line, int *i)
{
	if (line[*i] == '>' && line[*i + 1] != '>')
		return (0);
	else if (line[*i] == '<' && line[*i + 1] != '<')
		return (1);
	else if (line[*i] == '>' && line[*i + 1] == '>')
	{
		(*i)++;
		return (2);
	}
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		(*i)++;
		return (3);
	}
	return (-1);
}

void	ft_get_command_redirects(char *line, t_cmnds *command)
{
	int	i[5];

	ft_memset(i, 0, sizeof(int) * 5);
	i[0] = -1;
	command->redirs = ft_init_redirects(line);
	while (command->redirs && line[++i[0]])
	{
		ft_check_quotes(line[i[0]], &i[3], &i[4]);
		if (!i[3] && !i[4] && ft_strchr("<>", line[i[0]]))
		{
			i[1] = 0;
			command->redirs[i[2]] = (t_redirs *)malloc(sizeof(t_redirs));
			command->redirs[i[2]]->mode = ft_get_redirect_mode(line, &i[0]);
			command->redirs[i[2]]->filename = ft_get_filename(line, i);
			if (!command->redirs[i[2]++]->filename)
				fatal_error(MLC_ERROR);
			i[0] += i[1] - 1;
		}
	}
}
