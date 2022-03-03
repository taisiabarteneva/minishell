# include "minishell.h"

// temporary struct 

/* 
echo (-n)
cd
pwd
export
unset
env
exit
*/


int main(int ac, char **av, char **ev)
{
    t_env_vars 	*head;

    (void)ac;
    (void)av;

	if (ac != 1)
	{
		ft_putendl_fd("Usage: ./minishell", STDOUT_FILENO);
		return (0);
	}
	// ignore_signals();
    head = parse_env(ev);
	set_prompt(av, &head);
}