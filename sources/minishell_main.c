/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:21:34 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/07 20:09:10 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_envars	*envs;

	(void)argv;
	
	if (argc != 1)
		return (printf("Type commands after minishell is launched stupidass\n"));
	
	catch_signals();
	envs = ft_init_envars(envp);
	set_prompt(&envs);
	
	
	ft_envars_clear(&envs);
	return (0);
}
