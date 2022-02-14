#include "../funcs_for_lists/first_pars_list/main.h"
#include "./funcs_for_first_parse_step.h"

static char *ft_remove_bracers(char *string)
{
	char	*buf;
	int		i;
	int		index;

	while (1)
	{
		index = ft_strchr_index(string, '"');
		i = index;
		while (string[i] == '"')
			i++;
		if(string[i] == '\0')
			break;
		ft_memmove_without_return(&string[index], &string[i], ft_strlen(&string[i]) + 1);
	}
	index = ft_strchr_index(string, '"');
	buf = string;
	string = ft_strndup(string, index);
	free(buf);
	return (string);
}

static int ft_search_commands(char *string, char **arr_of_commands)
{
	int		i;

	i = 0;
	
	return(0);
}

t_first_pars_struct *ft_first_pars_step(char *string){

	t_first_pars_struct	*result_struct = NULL;
	char				**buf;
	char				**arr_of_commands;
	int					i;
	
	i = 0;
	buf = ft_updated_split(string, ' ');
	arr_of_commands = ft_split("echo cd pwd export unset env exit << >> < > |", ' ');
	while (buf[i])
	{
		if (ft_strchr(buf[i], '"'))
		{
			buf[i] = ft_remove_bracers(buf[i]);
		}
		ft_search_commands(buf[i], arr_of_commands);
		free(buf[i]);
		i++;
	}
	free(buf);
	while (arr_of_commands[i])
		free(arr_of_commands[i++]);
	free(arr_of_commands);

	return(result_struct);
}