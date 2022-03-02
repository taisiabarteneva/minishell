# include "../minishell.h"

typedef struct s_env_vars
{
    char    *key;
    char    *value;
    struct  s_env_vars *next;
    struct  s_env_vars *prev;
}              t_env_vars;

void fatal_error(char *msg)
{
    write(STDERR_FILENO, msg, ft_strlen(msg));
    exit(EXIT_FAILURE);
}

int count_env_vars(char **ev)
{
    int i;

    i = 0;
    while (ev[i])
        i++;
    return (i);
}

void add_node_to_list(char *line, t_env_vars **head)
{
    t_env_vars  *new_node;
    t_env_vars  *current;
    char        **key_value;

	key_value = NULL;
    new_node = (t_env_vars *)malloc(sizeof(t_env_vars));
    if (!new_node)
        fatal_error("malloc");
    if (!(*head))
    {
        *head = new_node;
        new_node->prev = NULL;
    }
    else
    {
        current = *head;
        while (current->next)
            current = current->next;
        current->next = new_node;
        new_node->prev = current;
    }
	if (line)
    	key_value = ft_split(line, '=');
    if (!key_value && !(*key_value))
        fatal_error("malloc");  
    new_node->next = NULL;
    new_node->key = key_value[0];
    new_node->value = key_value[1];
}

t_env_vars  *parse_env(char **ev)
{
    t_env_vars  *head;
    int         vars_count;
    int         i;

    vars_count = count_env_vars(ev);
	head = NULL;
    i = 0;
    while (i < vars_count)
    {
        add_node_to_list(*ev, &head);
        i++;
		ev++;
    }
    return (head);
}

void print_list(t_env_vars *head)
{
    t_env_vars *tmp;

    tmp = head;
    while (tmp)
    {
        printf("CURRENT NODE: [%s] [%s]\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
}

int main(int ac, char **av, char **ev)
{
    t_env_vars *head;

    (void)ac;
    (void)av;
    head = parse_env(ev);
    print_list(head);
}