/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 21:16:59 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/24 21:17:38 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void check_if_key_exists(t_envars **list, char *arg)
{
	char	**key_value;
	char	*exists;

	key_value = ft_split(arg, '=');
	exists = find_env_node(*list, key_value[0]);
	if (exists)
		ft_envar_del_one(list, arg);
	free(key_value);
}

int is_valid_env_key(char *token)
{
	int i;

	i = 0;
	if (!ft_isalpha(token[i]) && token[i] != '_')
		return (0);
	i++;
	while (token[i] != '\0')
	{
		if (!ft_isascii(token[i]))
			return (0);
		i++;
	}
	return (1);
}

int is_equal_sign(char *token)
{
	int i;

	i = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int get_list_size(t_envars *list)
{
	t_envars	*tmp;
	int			size_of_list;

	tmp = list;
	size_of_list = 0;
	while (tmp != NULL)
	{
		size_of_list++;
		tmp = tmp->next;
	}
	return (size_of_list);
}

char **get_sorted_keys(char **keys, int size_of_list)
{
	int 		i;
	int			j;
	char 		*tmp;

	i = 0;
	while (i < size_of_list)
	{
		j = 0;
		while (j < size_of_list - i - 1)
		{
			if (ft_strncmp(keys[j], keys[j + 1], ft_strlen(keys[j]) + 1) > 0)
			{
				tmp = keys[j];
				keys[j] = keys[j + 1];
				keys[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (keys);
}
