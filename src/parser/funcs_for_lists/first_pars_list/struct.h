#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_first_pars_struct
{
	char						*command;
	char						*args;
	char						*modificators;
	char						*result;
	struct s_first_pars_struct	*next;
	
} t_first_pars_struct;

#endif