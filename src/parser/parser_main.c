#include "./parser_main.h"
#include "./funcs_for_lists/first_pars_list/struct.h"

t_result_struct *parser(char *string)
{
	t_first_pars_struct	*first_struct;
	t_result_struct		*result = NULL;

	first_struct = ft_first_pars_step(string);
	return(result);
}