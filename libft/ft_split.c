/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:52:45 by wurrigon          #+#    #+#             */
/*   Updated: 2021/10/17 20:20:55 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_word_counter(char const *str, char sep)
{
	size_t	i;
	size_t	count;
	size_t	flag;

	i = 0;
	count = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] != sep && flag == 0)
		{
			flag = 1;
			count += 1;
		}
		else if (str[i] == sep && flag == 1)
			flag = 0;
		i++;
	}
	return (count);
}

static char	*ft_fill_elem(char *elem, const char *s, size_t len, size_t *j)
{
	size_t	tmp;
	size_t	i;

	i = 0;
	tmp = *j;
	while (*j < tmp + len)
	{
		elem[i] = s[*j];
		i++;
		(*j)++;
	}
	elem[i] = '\0';
	return (elem);
}

static char	*ft_init_elem(char const *s, char c, size_t *j)
{
	char	*elem;
	size_t	elem_len;
	size_t	tmp;

	elem_len = 0;
	while (s[*j] == c && s[*j])
		(*j)++;
	tmp = *j;
	while (s[tmp] != c && s[tmp])
	{
		tmp++;
		elem_len++;
	}
	elem = (char *)malloc(sizeof(char) * elem_len + 1);
	if (elem == NULL)
		return (NULL);
	return (ft_fill_elem(elem, s, elem_len, j));
}

static void	ft_free_memory(size_t count, char **arr)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		if (arr[i] == NULL)
		{
			while (i >= 0)
			{
				free(arr[i]);
				i--;
			}
			free(arr);
		}
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	size_t	word_count;
	size_t	i;
	size_t	j;
	char	**arr;

	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	word_count = ft_word_counter(s, c);
	arr = (char **) malloc(sizeof(char *) * (word_count + 1));
	if (arr == NULL)
		return (NULL);
	arr[word_count] = NULL;
	while (i < word_count)
	{
		arr[i] = ft_init_elem(s, c, &j);
		i++;
	}
	ft_free_memory(word_count, arr);
	return (arr);
}
