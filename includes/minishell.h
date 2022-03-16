/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:18:03 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/16 22:38:49 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "../libft/libft.h"
# include "../readline/tilde.h"
# include "../readline/rlconf.h"
# include "../readline/rlstdc.h"
# include "../readline/history.h"
# include "../readline/keymaps.h"
# include "../readline/readline.h"
# include "../readline/chardefs.h"
# include "../readline/rltypedefs.h"

# define MAX_PATH 1024

# define CMD_ERROR 		"minishell: parsing error\n"
# define MLC_ERROR 		"minishell: memory allocation error\n"
# define EXEC_ERROR 	"minishell: execve error\n"
# define FORK_ERR		"minishell: fork error\n"
# define WAITPID_ERR	"minishell: waitpid error\n"

// Exit status

# define EXIT_ERR 1

// General shell structure.

typedef struct s_shell
{
	int				exit_status;
	int				shell_level;
	int				fd_in;
	int				fd_out;
}				t_shell;

// Environment variables list structure.

typedef struct s_envars
{
	char				*key;
	char				*value;
	struct s_envars		*next;
}	t_envars;

// Commands list structure.

typedef struct s_redirs
{
	char	*filename;
	int		mode;
}	t_redirs;

typedef struct s_comnds
{
	t_redirs		**redirs;
	t_list			*args;
	t_envars		*envs;
}	t_cmnds;

// Command Parser.

void		ft_check_quotes(char c, int *inside_s_quote, int *inside_d_quote);
void		ft_get_command_arguments(char *line, t_cmnds *command);
void		ft_get_command_redirects(char *line, t_cmnds *command);
char		*ft_remove_quotes(char *str, t_envars *envs);
t_cmnds		**ft_parse_input(char *str, t_envars *envs);
void		ft_commands_clear(t_cmnds **commands);
int			ft_check_line_part_one(char *str);
int			ft_check_line_part_two(char *str);
char		*ft_remove_redirects(char *str);
char		*ft_remove_spaces(char *str);

// Environment Variables Parser.

void		ft_envar_add_back(t_envars **vars, t_envars *new_var);
char		*find_env_node(t_envars *list, const char *key);
void		ft_envar_del_one(t_envars **vars, char *key);
t_envars	*ft_envar_new(char *key, char *value);
void		ft_envars_clear(t_envars **vars);
void		ft_print_envars(t_envars *vars);
t_envars	*ft_init_envars(char **envp);
int			get_args_quantity(t_list *args);


// Readline and prompt.

void		rl_replace_line(const char *text, int clear_undo);
void		set_shell(t_envars **envs, t_shell *shell, char **envp);
void		add_line_to_history(char *line);
char		*read_prompt_line(void);

// Utilities.

void		set_shell_level(t_envars *envs, t_shell *shell);
void		fatal_error(char *msg);

// Signals.

void		tty_hide_input(void);
void		catch_signals(void);
void		set_signals(void);
void		*sigint_handler(int sig_num);


// Built-ins.

int			is_built_in(char *command);
void		built_ins(t_envars **list, t_cmnds *commands, t_shell *shell, char **envp);
void		execute_export(t_envars **list, t_list *args, t_shell *shell);
void		execute_unset(t_envars **list, t_list *args, t_shell *shell);
void		execute_cd(t_envars **list, t_list *args, t_shell *shell);
void		execute_exit(t_shell *shell, t_list *args);
void		execute_echo(t_list *args, t_shell *shell);
void		execute_pwd(t_shell *shell, t_list *args);
void		execute_env(t_envars *list, t_shell *shell, t_list *args);

// Executor.

void		execute_command(t_cmnds *command, t_shell *shell, char **envp);

// Binary.

void		execute_bin(t_cmnds *command, t_shell *shell, char **envp);
char		**get_command_arguments(t_list *args);


#endif