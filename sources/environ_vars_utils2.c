/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_vars_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:33:11 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/09 18:21:43 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_envars	*ft_envar_new(char *key, char *value)
{
	t_envars	*var;

	var = (t_envars *)malloc(sizeof(t_envars));
	if (!var)
		return (NULL);
	var->key = key;
	var->value = value;
	var->next = NULL;
	return (var);
}

void	ft_envar_add_back(t_envars **vars, t_envars *new_var)
{
	t_envars	*copy;

	copy = *vars;
	if (!(*vars))
	{
		new_var->next = *vars;
		*vars = new_var;
	}
	else
	{
		while (copy->next)
			copy = copy->next;
		copy->next = new_var;		
		new_var->next = NULL;
	}
}

void	ft_envar_del_one(t_envars **vars, char *key)
{
	t_envars	*curr;
	t_envars	*prev;

	if (!(*vars) || !key)
		return ;
	prev = NULL;
	curr = *vars;
	while (curr && ft_strncmp(curr->key, key, ft_strlen(key) + 1))
	{
		prev = curr;
		curr = curr->next;
	}
	// free(curr->key);
	// free(curr->value);
	if (prev)
		prev->next = curr->next;
	else
		*vars = curr->next;
	free(curr);
}

void	ft_envars_clear(t_envars **vars)
{
	t_envars	*prev;

	if (!(*vars))
		return ;
	prev = NULL;
	while (*vars)
	{
		prev = (*vars);
		(*vars) = (*vars)->next;
		if (prev)
		{
			free(prev->key);
			free(prev->value);
			free(prev);
		}
	}
	*vars = NULL;
}
