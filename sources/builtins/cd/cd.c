/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:42:12 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/24 22:02:19 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	change_old_pwd_environ(t_envars **list, char *old_path)
{
	t_envars	*old_pwd_node;

	old_pwd_node = ft_envar_new("OLD_PWD", ft_strdup(old_path));
	if (!old_pwd_node)
		fatal_error(MLC_ERROR);
	ft_envar_del_one(list, "OLD_PWD");
	ft_envar_add_back(list, old_pwd_node);
}

void	change_new_pwd_environ(t_envars **list, char *new_path)
{
	t_envars	*new_pwd_node;
	t_envars	*tmp;

	tmp = *list;
	new_pwd_node = ft_envar_new("PWD", ft_strdup(new_path));
	if (!new_pwd_node)
		fatal_error(MLC_ERROR);
	ft_envar_del_one(list, "PWD");
	ft_envar_add_back(list, new_pwd_node);
}

void	handle_cd_arguments(t_list *args, t_shell **shell, t_envars *list)
{
	int		status;
	char	tmp_path[MAX_PATH];

	status = 0;
	if (args->next && !ft_strncmp(args->next->content, "-", 1)
		&& ft_strlen(args->next->content) == 1)
	{
		if (find_env_node(list, "OLD_PWD") == NULL)
		{
			write(STDERR_FILENO, "bash: cd: OLDPWD not set\n", 25);
			(*shell)->exit_status = EXIT_ERR;
			return ;
		}
		else
		{
			status = chdir(find_env_node(list, "OLD_PWD"));
			getcwd(tmp_path, MAX_PATH);
			write(STDOUT_FILENO, tmp_path, ft_strlen(tmp_path) + 1);
			write(1, "\n", 1);
		}
	}
	else
		status = chdir(args->next->content);
	if (status == -1)
		handle_non_existing_path(args, shell);
}

void	execute_cd(t_envars **list, t_list *args, t_shell **shell)
{
	int		status;
	char	old_path[MAX_PATH];
	char	new_path[MAX_PATH];

	(*shell)->exit_status = 0;
	status = 0;
	getcwd(old_path, MAX_PATH);
	if (args->next == NULL)
		handle_empty_input(*list, shell);
	else
		handle_cd_arguments(args, shell, *list);
	if (getcwd(new_path, MAX_PATH) == NULL)
	{
		write(STDERR_FILENO, PARENT_DIR, ft_strlen(PARENT_DIR) + 1);
		return ;
	}
	change_new_pwd_environ(list, new_path);
	change_old_pwd_environ(list, old_path);
}
