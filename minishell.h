# ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libft/libft.h>

typedef struct s_env_vars
{
    char    *key;
    char    *value;
    struct  s_env_vars *next;
    struct  s_env_vars *prev;
}              t_env_vars;

/* env */
t_env_vars  *parse_env(char **ev);

/* utils */
void 		print_list(t_env_vars *head);
void 		fatal_error(char *msg);

/* prompt */
void		set_prompt(void);

#endif