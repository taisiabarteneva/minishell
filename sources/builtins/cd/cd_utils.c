/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 21:03:44 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/24 21:05:15 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../includes/minishell.h"

void handle_unset_home(t_shell **shell)
{
	write(STDERR_FILENO, "minishell: cd: ", 15);
	write(STDERR_FILENO, "HOME not set\n", 14);
	(*shell)->exit_status = EXIT_ERR;
}

void handle_empty_input(t_envars *list, t_shell **shell)
{
	char		*root_path;
	int			status;

	root_path = find_env_node(list, "HOME");
	status = chdir(root_path);
	if (status == -1)
		handle_unset_home(shell);
}

void handle_non_existing_path(t_list *args, t_shell **shell)
{
	write(STDERR_FILENO, "minishell: cd: ", 15);
	write(STDERR_FILENO, args->next->content, ft_strlen(args->next->content));
	write(STDERR_FILENO, ": No such file or directory\n", 29);
	(*shell)->exit_status = EXIT_ERR;
}