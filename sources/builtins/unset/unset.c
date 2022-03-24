/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:42:26 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/24 21:22:03 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool is_valid_env_name(const char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (false);
	str++;
	while (*str != '\0')
	{
		if (!ft_isalnum(*str) && *str != '+' && *str != '*' && *str != '_')
			return (false);
		str++;
	}
	return (true);
}

void execute_unset(t_envars **list, t_list *args, t_shell **shell)
{
	while (args)
	{
		if (is_valid_env_name(args->content) == false)
		{
			(*shell)->exit_status = EXIT_ERR;
			write(STDERR_FILENO, "minishell: unset: `", 19);
			write(STDERR_FILENO, args->content, ft_strlen(args->content));
			write(STDERR_FILENO, "': not a valid identifier\n", 27);
		}
		else
		{
			ft_envar_del_one(list, args->content);
			(*shell)->exit_status = 0;
		}
		args = args->next;
	}
}