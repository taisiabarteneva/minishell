# include "minishell.h"

/* 
echo -n +
cd		
pwd		+
export	
unset 	+
env   	+
exit  	+
*/
int main(int ac, char **av, char **ev)
{
    t_env_vars 	*envs;
	
    (void)ac;
    (void)av;
	envs = NULL;

	catch_signals();
    envs = parse_env(ev);
	set_prompt(av, &envs);
}