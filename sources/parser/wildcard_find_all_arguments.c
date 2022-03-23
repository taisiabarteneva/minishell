/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_find_all_arguments.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:37:00 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/22 20:30:00 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static int	ft_check_wildcard_argument_loop(char **pieces, int *j,
// 	char *new_arg, int *i)
// {
// 	if (*j && pieces[*j] && pieces[*j][0])
// 	{
// 		if (!ft_strncmp(&new_arg[*i], pieces[*j], ft_strlen(pieces[*j])))
// 		{
// 			(*i) += ft_strlen(pieces[*j]) - 1;
// 			(*j)++;
// 		}
// 	}
// 	else if (!j && pieces[*j] && pieces[*j][0])
// 	{
// 		if (!ft_strncmp(new_arg, pieces[*j], ft_strlen(pieces[*j])))
// 		{
// 			(*i) = ft_strlen(pieces[*j]) - 1;
// 			(*j)++;
// 		}
// 		else
// 			return (1);
// 	}
// 	return (0);
// }

// static int	ft_check_wildcard_argument(char **pieces, char *new_arg)
// {
// 	int		j;
// 	int		i;

// 	j = 0;
// 	i = -1;
// 	if ((new_arg[0] == '.' && ft_strlen(new_arg) == 1)
// 		|| (!ft_strncmp("..", new_arg, 2) && ft_strlen(new_arg) == 2))
// 		return (0);
// 	if (pieces[j] && !pieces[j][0])
// 		j++;
// 	while (new_arg[++i] && pieces[j])
// 		if (ft_check_wildcard_argument_loop(pieces, &j, new_arg, &i))
// 			break ;
// 	if (pieces[j] && !pieces[j][0])
// 		j++;
// 	if (!pieces[j])
// 		return (1);
// 	return (0);
// }

// static t_list	*ft_get_new_argumnets(char **pieces)
// {
// 	t_list			*new_args;
// 	t_list			*new_arg;
// 	DIR				*dirp;
// 	struct dirent	*dp;

// 	dirp = opendir("./");
// 	new_args = NULL;
// 	while (dirp)
// 	{
// 		dp = readdir(dirp);
// 		if (!dp)
// 		{
// 			closedir(dirp);
// 			return (new_args);
// 		}
// 		if (ft_check_wildcard_argument(pieces, dp->d_name))
// 		{
// 			printf("%s\n", dp->d_name);
// 			new_arg = ft_lstnew(ft_strdup(dp->d_name));
// 			if (!new_arg)
// 				fatal_error(MLC_ERROR);
// 			ft_lstadd_back(&new_args, new_arg);
// 		}
// 	}
// 	return (NULL);
// }

// static char	**ft_init_and_get_pieces(char *str, t_envars *envs)
// {
// 	char	**pieces;
// 	int		i;

// 	i = -1;
// 	pieces = ft_init_wildcard_pieces(str);
// 	if (!pieces)
// 		fatal_error(MLC_ERROR);
// 	ft_get_wildcard_pieces(str, pieces);
// 	while (pieces[++i])
// 		pieces[i] = ft_remove_quotes(pieces[i], envs);
// 	return (pieces);
// }

// int	ft_replace_wildcards(t_cmnds *command, t_list *args_copy)
// {
// 	t_list	*new_args;
// 	char	**pieces;

// 	while (args_copy)
// 	{
// 		pieces = ft_init_and_get_pieces(args_copy->content, command->envs);
// 		new_args = ft_get_new_argumnets(pieces);
// 		if (new_args)
// 		{
// 			printf("FERE\n");
// 			ft_lst_insert_lst(&command->args, args_copy, new_args);
// 			new_args = args_copy;
// 			args_copy = args_copy->next;
// 			ft_lst_del_value(&command->args, new_args->content);
// 		}
// 		else
// 		{
// 			args_copy->content = ft_remove_quotes(args_copy->content,
//					command->envs);
// 			args_copy = args_copy->next;
// 		}
// 		ft_array_clear(&pieces);
// 	}
// 	return (0);
// }
