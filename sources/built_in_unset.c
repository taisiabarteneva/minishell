#include "../includes/minishell.h"

void execute_unset(t_envars **list, char *key)
{
	t_envars *next;
	t_envars *tmp;

	tmp = *list;

	if (tmp && tmp->next)
	{
		while (tmp)
		{
			if (ft_strlen(tmp->key) == ft_strlen(key) 
				&& ft_strncmp((const char *)tmp->key,
				(const char *)key, ft_strlen(key)) == 0)
			{
				if (tmp->next != NULL)
				{
					next = tmp->next;
				}
				else
					next = NULL;
			}
			if (tmp->next != NULL)
				tmp = tmp->next;
			else
				break ; 
		}
	}
}