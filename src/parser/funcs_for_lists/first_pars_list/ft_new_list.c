#include "./struct.h"
#include<stdlib.h>

t_first_pars_struct *ft_new_list(char *command)
{
	t_first_pars_struct *new_list;

	new_list = malloc(sizeof(t_first_pars_struct));
	new_list->command = command;
	new_list->next = NULL;
	return (new_list);
}
