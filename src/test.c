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

void add_node_to_list(char *line, t_env_vars *head)
{
    t_env_vars  *new_node;
    t_env_vars  *current;
    char        **key_value;

    new_node = malloc(sizeof(t_env_vars));
    if (!new_node)
        fatal_error("malloc");
    if (!head)
    {
        head = new_node;
        new_node->prev = NULL;
    }
    else
    {
        current = head;
        while (current->next)
            current = current->next;
        current->next = new_node;
        new_node->prev = current;
    }
    key_value = ft_split(line, '=');
    if (!key_value && !(*key_value))
        fatal_error("malloc");
    new_node->next = NULL;
    new_node->key = key_value[0];
    new_node->value = key_value[1];
}

t_env_vars  *parse_env(char **ev)
{
    t_env_vars  *head;;
    int         vars_count;
    int         counter;

    // head = NULL;
    vars_count = count_env_vars(ev);
    head = malloc(sizeof(t_env_vars) * vars_count);
    if (!head)
        fatal_error("malloc");
    counter = 0;
    while (counter < vars_count)
    {
        add_node_to_list(*ev, head);
        counter++;
        ev++;
    }
    return (head);
}

void print_list(t_env_vars *head)
{
    t_env_vars *tmp;

    tmp = head;
    while (tmp->next)
    {
        tmp = tmp->next;
        printf("PREV KEY IS [%s]\n", tmp->prev->key);
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