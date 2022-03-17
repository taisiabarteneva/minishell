/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:21:34 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/17 15:04:28 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_envars	*envs;
	t_shell		*shell;

	(void)argv;
	shell = NULL;
	shell = malloc(sizeof(t_shell));
	if (argc != 1)
		return (printf("Type commands after minishell is launched stupidass\n"));
	envs = ft_init_envars(envp);
	set_shell_level(envs, shell);
	shell->exit_status = 0;
	tty_hide_input();
	catch_signals();
	set_shell(&envs, &shell, envp);
	ft_envars_clear(&envs);
	return (shell->exit_status);
}
