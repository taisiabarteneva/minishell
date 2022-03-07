/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_vars_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 22:49:33 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/07 19:46:57 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fatal_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

t_envars	*ft_init_envars(char **envp)
{
	char		**key_value;
	t_envars	*envars;
	t_envars	*var;
	int			i;

	envars = NULL;
	if (!envp)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		key_value = ft_split(envp[i], '=');
		if (!key_value)
			fatal_error(MLC_ERROR);
		var = ft_envar_new(key_value[0], key_value[1]);
		if (!var)
			fatal_error(MLC_ERROR);
		ft_envar_add_back(&envars, var);
		free(key_value);
	}
	return (envars);
}

void	ft_print_envars(t_envars *vars)
{
	while (vars)
	{
		// printf("%s=%s\n", vars->key, vars->value);
		vars = vars->next;
	}
}
