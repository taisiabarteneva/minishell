#ifndef FUNCS_FOR_FIRST_PARS_STEP_H
# define FUNCS_FOR_FIRST_PARS_STEP_H
# include"../../../libft/libft.h"
// надо переименовать файл

typedef struct s_updated_split_list
{
	char						*string;
	char						*modificator;
	char						*type;
	struct s_updated_split_list	*next;	
}	t_updated_split_list;

// t_updated_split_list *ft_updated_split(char *string, char **arr_of_sep)
char	**ft_updated_split(char *s, char c);
char	*ft_strndup(char *str,int len);
void	ft_memmove_without_return(void *dest, void *src, size_t len);
int		ft_strchr_index(char *string, int symbol);

#endif