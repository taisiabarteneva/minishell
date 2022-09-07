/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:18:03 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/24 22:47:29 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>
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

# define MAX_PATH 	1024

# define LLU 		9223372036854775807

# define CMD_ERROR 		"minishell: parsing error\n"
# define MLC_ERROR 		"minishell: memory allocation error\n"
# define EXEC_ERROR 	"minishell: execve error\n"
# define FORK_ERR		"minishell: fork error\n"
# define WAITPID_ERR	"minishell: waitpid error\n"
# define WLC_ERROR		"minishell: no matches found: %s\n"
# define PIPES_ERR		"minishell: pipes error\n"
# define PARENT_DIR		"cd: error retrieving current directory: getcwd: \
			cannot access parent directories: No such file or directory\n"
# define FORK_ERROR		"minishell: fork: Resource temporarily unavailable\n"

/* Exit status codes */
# define EXIT_ERR			1
# define EXIT_FORK_ERR 		128
# define EXIT_BIG_NUM		255
# define EXIT_NON_NUMERIC	255

/* Main shell struct */
typedef struct s_shell
{
	int				exit_status;
	int				shell_level;
	int				fd_in;
	int				fd_out;
	int				process_count;
	int				**pipes;
}				t_shell;

/* Structure to strore environment variables */
typedef struct s_envars
{
	char				*key;
	char				*value;
	struct s_envars		*next;
}	t_envars;

typedef struct s_redirs
{
	char	*filename;
	int		mode;
}	t_redirs;

/* Structure to store commands from input */
typedef struct s_comnds
{
	t_redirs		**redirs;
	t_list			*args;
	t_envars		*envs;
	t_shell			*shell;
}	t_cmnds;

/* Commands parser */
void		ft_check_quotes(char c, int *inside_s_quote, int *inside_d_quote);
t_cmnds		**ft_parse_input(char *str, t_envars *envs, t_shell *shell);
void		ft_get_command_arguments(char *line, t_cmnds *command);
void		ft_get_command_redirects(char *line, t_cmnds *command);
char		*ft_remove_quotes(char *str, t_cmnds *command);
void		ft_commands_clear(t_cmnds ***commands);
int			ft_check_line_part_one(char *str);
int			ft_check_line_part_two(char *str);
char		*ft_remove_redirects(char *str);
char		*ft_remove_spaces(char *str);

/* Environment variables parser */
void		ft_envar_add_back(t_envars **vars, t_envars *new_var);
char		*find_env_node(t_envars *list, const char *key);
void		ft_envar_del_one(t_envars **vars, char *key);
t_envars	*ft_envar_new(char *key, char *value);
void		ft_envars_clear(t_envars **vars);
void		ft_print_envars(t_envars *vars);
int			get_args_quantity(t_list *args);
t_envars	*ft_init_envars(char **envp);

/* Readline */
void		set_shell(t_envars **envs, t_shell **shell, char **envp);
void		rl_replace_line(const char *text, int clear_undo);
void		add_line_to_history(char *line);
char		*read_prompt_line(void);

/* Utilities */
void		set_shell_level(t_envars *envs, t_shell *shell);
void		fatal_error(char *msg);

/* Signals */
void		tty_hide_input(void);
void		catch_signals(void);
void		*sigint_handler(int sig_num);
void		sig_heredoc(int sig);
void		c_fork(int signum);
void		sigquit_handler(int num);
void		*sig_fork(int num);
void		return_signals_parent_process(void);
void		set_signals(t_cmnds **commands);

/* Builtins */
int			is_built_in(char *command);
void		built_ins(t_envars **list, t_cmnds *commands, t_shell **shell,
				char **envp);

/* cd builtin */
void		execute_cd(t_envars **list, t_list *args, t_shell **shell);
void		handle_non_existing_path(t_list *args, t_shell **shell);
void		handle_empty_input(t_envars *list, t_shell **shell);

/* echo builtin */
void		execute_echo(t_list *args, t_shell **shell);

/* env builtin */
void		execute_env(t_envars *list, t_shell **shell);

/* export builtin */
void		execute_export(t_envars **list, t_list *args, t_shell **shell);
void		check_if_key_exists(t_envars **list, char *arg);
char		**get_sorted_keys(char **keys, int size_of_list);
int			is_valid_env_key(char *token);
int			is_equal_sign(char *token);
int			get_list_size(t_envars *list);

/* unset builtin */
void		execute_unset(t_envars **list, t_list *args, t_shell **shell);
void		execute_exit(t_shell **shell, t_list *args);
void		execute_pwd(t_shell **shell, t_list *args, t_envars *list);

/* ---------------------------------------------------------- Executor */
int			handle_redirects(t_cmnds *command, t_shell **shell, int in);
void		launch_command(t_cmnds *command, char **envp, t_shell **shell);
void		wait_child_processes(t_shell **shell, pid_t id);
void		fork_error(t_shell **shell);
void		exec_system_bin(t_cmnds *command, char **path, char ***cmd_args);
void		exec_non_system_bin(t_cmnds *command, char **path, char ***cmdargs);
void		get_command_position(t_cmnds *command, t_shell **shell, int cmd_pos,
				int in);

/* Heredoc */
void		here_doc(char *del, t_shell **shell, int in);

/* Pipes */
void		open_pipes(int **pipes, int cmnds);
void		close_all_pipes(int **pipes);
int			**pipes_loop(int cmnds);

/* Binary */
void		execute_bin(t_cmnds **commands, t_shell **shell, char **envp,
				int in);
char		**get_command_arguments(t_list *args);
void		get_command_position(t_cmnds *command, t_shell **shell, int cmd_pos,
				int in);

/* Wildcard replacement */
void		ft_lst_insert_lst(t_list **lst1, t_list *curr, t_list *lst2);
int			ft_replace_wildcards(t_cmnds *command, t_list *args_copy);
void		ft_get_wildcard_pieces(char *str, char **pieces);
void		ft_lst_del_value(t_list **lst, char *value);
void		ft_free_command_redirects(t_cmnds *command);
char		**ft_init_wildcard_pieces(char *str);
int			ft_check_for_dollarsign(char *str);
int			ft_array_clear(char ***array);

#endif