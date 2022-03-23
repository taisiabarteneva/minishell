/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:41:59 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/16 15:03:12 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char **handle_export_without_args(t_envars *list)
{
	int 	size;
	char	**tmp;
	int		i;
	
	size = get_list_size(list);
	tmp = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
	if (!tmp)
		fatal_error(MLC_ERROR);
	while (list)
	{
		tmp[i] = ft_strjoin(list->key, "=", 0, 0);			// check leaks
		tmp[i] = ft_strjoin(tmp[i], list->value, 0, 0); 	// check leaks
		if (tmp[i] == NULL)
			fatal_error(MLC_ERROR);
		list = list->next;
		i++;
	}
	tmp[i] = NULL;
	tmp = get_sorted_keys(tmp, size);
	return (tmp);
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

void display_sorted_list(char **sorted_keys)
{
	int 	i;
	
	i = 0;
	while (sorted_keys[i] != NULL)
	{
		write(STDOUT_FILENO, "declare -x ", 11);
		write(STDOUT_FILENO, sorted_keys[i], ft_strlen(sorted_keys[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

void add_env_key_value_pair(t_envars **list, char *arg)
{
	char		**key_value;
	t_envars	*new_node;
	
	key_value = ft_split(arg, '=');
	if (!key_value)
		fatal_error(MLC_ERROR);
	new_node = ft_envar_new(key_value[0], key_value[1]);
	if (!new_node)
		fatal_error(MLC_ERROR);
	ft_envar_add_back(list, new_node);
	free(key_value);		
}

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

void execute_export(t_envars **list, t_list *args, t_shell *shell)
{
	int		i;
	char 	**sorted_keys;
	t_list	*curr;

	i = 1;
	sorted_keys = NULL;
	curr = args->next;
	if (!curr)
	{
		shell->exit_status = 0;		
		sorted_keys = handle_export_without_args(*list);
		display_sorted_list(sorted_keys);
	}
	else
	{
		while (curr)
		{
			if (!is_valid_env_key(curr->content))
			{
				shell->exit_status = EXIT_ERR;
				write(STDERR_FILENO, "minishell: export: `", 20);
				write(STDERR_FILENO, curr->content, ft_strlen(curr->content));
				write(STDERR_FILENO, "': not a valid identifier\n", 27);
			}
			else if (!is_equal_sign(curr->content))
				shell->exit_status = 0;
			else
			{	
				shell->exit_status = 0;
				check_if_key_exists(list, curr->content);
				add_env_key_value_pair(list, curr->content);
			}
			curr = curr->next;
		}
	}
}