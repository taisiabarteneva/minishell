#include"./first_pars_step.h"
#include"./funcs_for_first_parse_step.h"

static void	*free_all(char **new, long long int i, long long int max)
{
	free(new[max]);
	while (i >= 0)
	{
		free(new[i]);
		i--;
	}
	free(new);
	return (NULL);
}	

int	*ft_search_quotesrs_indexes(char *s, int i, int *quotes_indexes, char c)
{
	quotes_indexes[0] = ft_strchr_index(&s[i], '"') + i;
	quotes_indexes[1] = ft_strchr_index(&s[quotes_indexes[0] + 1], '"') + quotes_indexes[0] + 1;
	while (s[quotes_indexes[1] + 1] != c && s[quotes_indexes[1] + 1] != '\0')
	{
		quotes_indexes[1] = ft_strchr_index(&s[quotes_indexes[1] + 1], '"') + quotes_indexes[1] + 1;
		quotes_indexes[1] = ft_strchr_index(&s[quotes_indexes[1] + 1], '"') + quotes_indexes[1] + 1;
		if (s[quotes_indexes[1]] == '\0')
			break;
	}
	return (quotes_indexes);
}

static int	skip_c(long long int i, char   *s, char c)
{
	while (s[i] == c && s[i] != '\0')
		i++;
	return (i);
}

static long long int	arr_count_counter(  char *s, \
			 long long int i, char c)
{
	long long int	arr_count;
	int				*quotes_indexes; // 0 - open; 1 - close

	quotes_indexes = malloc(sizeof(int) * 2);
	if (ft_strchr(s, '"'))
		quotes_indexes = ft_search_quotesrs_indexes(s, 0, quotes_indexes, c);
	else
	{
		quotes_indexes[0] = ft_strlen(s);
		quotes_indexes[1] = ft_strlen(s);
	}
	if (s[i] != c && s[i] && s[i] != '\"')
		arr_count = 1;
	else
		arr_count = 0;
	while (s[i] != '\0')
	{
		if (i == quotes_indexes[0])
		{
			arr_count++;
			i = quotes_indexes[1];
			quotes_indexes = ft_search_quotesrs_indexes(s, i + 1, quotes_indexes, c);
		}else if (s[i] == c)
		{
			i = skip_c(i, s, c);
			if (s[i] != c && s[i] != '\0')
				arr_count++;
		}
		if (s[i] != '\0')
			i++;
	}
	free(quotes_indexes);
	return (arr_count);
}

static char	**ft_main_logic(long long int arr_count, \
			  char *s, char c, char **new)
{
	long long int	ii;
	long long int	iii;
	long long int	i;
	int				*quotes_indexes; // 0 - open; 1 - close

	quotes_indexes = malloc(sizeof(int) * 2);
	ii = 0;
	iii = 0;
	i = skip_c(0, s, c);
	while (arr_count >= iii)
	{
		ii = 0;
		if (s[i] == '"')
		{
			quotes_indexes = ft_search_quotesrs_indexes(s, i, quotes_indexes, c);
			i = quotes_indexes[1] + 1;
			ii = quotes_indexes[1] - quotes_indexes[0] + 1;
		}
		else
		{
			while (s[i] != c
			&& s[i] != '\0')
			{	
				ii++;
				i++;
			}
		}
		new[iii] = malloc(sizeof(char) * ii);
		if (new[iii] == NULL)
			return (free_all(new, iii, arr_count));
		ft_strlcpy(new[iii], &s[i - ii], ii + 1);
		iii++;
		i = skip_c(i, s, c);
	}
	free(quotes_indexes);
	return (new);
}

char	**ft_updated_split(char   *s, char c)
{
	long long int	i;
	long long int	arr_count;
	char			**new;

	if (s == NULL)
		return (NULL);
	i = 0;
	i = skip_c(i, s, c);
	arr_count = arr_count_counter(s, i, c);
	new = (char **)malloc(sizeof(char *) * (arr_count + 1));
	if (new == NULL)
		return (NULL);
	new[arr_count--] = NULL;
	new = ft_main_logic(arr_count, s, c, new);
	return (new);
}
