# ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libft/libft.h>
# include <dirent.h>

typedef struct s_env_vars
{
    char    *key;
    char    *value;
    struct  s_env_vars *next;
    struct  s_env_vars *prev;
}              t_env_vars;

// typedef struct s_storage
// {
// 	char 	*cmd;
// 	int 	fd_in;
// 	int 	fd_out;
// 	char	*cmd2;
// }				t_storage;

/* env */
t_env_vars  *parse_env(char **ev);

/* utils */
void 		print_list(t_env_vars *head);
void 		fatal_error(char *msg);

/* prompt */
void		set_prompt(char **av, t_env_vars **list);

/* built_ins */
void 		built_ins(char *cmd, t_env_vars **list);


#endif