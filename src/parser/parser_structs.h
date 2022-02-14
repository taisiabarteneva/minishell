#ifndef PARSER_STRUCTS_H
# define PARSER_STRUCTS_H

typedef struct s_result_struct
{
	char					*command;
	char					**args;
	char					*result;
	struct s_result_struct	*next;
	struct s_result_struct	*previous;
}	t_result_struct;

#endif
