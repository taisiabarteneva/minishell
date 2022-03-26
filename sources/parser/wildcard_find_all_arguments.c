/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_find_all_arguments.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:37:00 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/25 18:59:40 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_check_wildcard_argument_part_two(char **pieces, int *i,
	char **curr, char **next)
{
	while (pieces[*i] && pieces[*i][0] && pieces[*i + 1])
	{
		*next = ft_strchr(*curr, pieces[*i][0]);
		if (!*next || ft_strlen(*next) < ft_strlen(pieces[*i]))
			return (0);
		*curr = *next;
		if (!ft_strncmp(*curr, pieces[*i], ft_strlen(pieces[*i])))
			(*i)++;
	}
	if (pieces[*i] && pieces[*i][0])
	{
		*next = ft_strrchr(*curr, pieces[*i][0]);
		if (!*next || *next - *curr < 0
			|| ft_strlen(*next) != ft_strlen(pieces[*i]))
			return (0);
		*curr = *next;
		if (ft_strncmp(*curr, pieces[*i], ft_strlen(*curr)))
			return (0);
	}
	return (1);
}

static int	ft_check_wildcard_argument(char **pieces, char *new_arg)
{
	char	*curr;
	char	*next;
	int		i;

	i = 0;
	curr = new_arg;
	next = NULL;
	if (ft_strlen(pieces[0]) > ft_strlen(new_arg))
		return (0);
	if (pieces[i][0] && ft_strncmp(curr, pieces[i], ft_strlen(pieces[i])))
		return (0);
	else if (pieces[i][0] && !ft_strncmp(curr, pieces[i], ft_strlen(pieces[i])))
		curr = &new_arg[ft_strlen(pieces[i])];
	i++;
	if (!ft_check_wildcard_argument_part_two(pieces, &i, &curr, &next))
		return (0);
	return (1);
}

static t_list	*ft_get_new_argumnets(char **pieces)
{
	t_list			*new_args;
	t_list			*new_arg;
	DIR				*dirp;
	struct dirent	*dp;

	dirp = opendir("./");
	new_args = NULL;
	while (dirp)
	{
		dp = readdir(dirp);
		if (!dp)
		{
			closedir(dirp);
			return (new_args);
		}
		if (ft_check_wildcard_argument(pieces, dp->d_name))
		{
			new_arg = ft_lstnew(ft_strdup(dp->d_name));
			if (!new_arg)
				fatal_error(MLC_ERROR);
			ft_lstadd_back(&new_args, new_arg);
		}
	}
	return (NULL);
}

static char	**ft_init_and_get_pieces(char *str, t_cmnds *command)
{
	char	**pieces;
	int		i;

	i = -1;
	if (!ft_check_for_dollarsign(str))
	{
		pieces = ft_init_wildcard_pieces(str);
		if (!pieces)
			fatal_error(MLC_ERROR);
		ft_get_wildcard_pieces(str, pieces);
	}
	else
		pieces = NULL;
	while (pieces && pieces[++i])
		pieces[i] = ft_remove_quotes(pieces[i], command);
	return (pieces);
}

int	ft_replace_wildcards(t_cmnds *command, t_list *args_copy)
{
	t_list	*new_args;
	char	**pieces;

	while (args_copy)
	{
		new_args = NULL;
		pieces = ft_init_and_get_pieces(args_copy->content, command);
		if (pieces && pieces[1])
			new_args = ft_get_new_argumnets(pieces);
		if (new_args)
		{
			ft_lst_insert_lst(&command->args, args_copy, new_args);
			new_args = args_copy;
			args_copy = args_copy->next;
			ft_lst_del_value(&command->args, new_args->content);
		}
		else
		{
			args_copy->content = ft_remove_quotes(args_copy->content,
					command);
			args_copy = args_copy->next;
		}
		ft_array_clear(&pieces);
	}
	return (0);
}
