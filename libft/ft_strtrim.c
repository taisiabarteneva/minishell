/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 10:13:19 by wurrigon          #+#    #+#             */
/*   Updated: 2022/02/10 14:25:19 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_trim_char_counter(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	size_t	count;

	i = 0;
	len = ft_strlen(s1);
	count = len;
	while (s1[i] && ft_strchr(set, s1[i]))
	{
		i++;
		count--;
	}
	if (count == 0)
		return (count);
	while (len >= 0 && ft_strchr(set, s1[len]))
	{
		len--;
		count--;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	tmp;
	size_t	i;
	size_t	j;
	char	*res;

	if (s1 == NULL)
		return (NULL);
	if (ft_strncmp(s1, "", 1) == 0)
		return (ft_strdup(""));
	len = ft_trim_char_counter(s1, set);
	if (len == 0)
		return (ft_strdup(""));
	res = (char *)malloc(len + 2);
	if (res == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	tmp = i;
	while (i < tmp + len + 1)
		res[j++] = s1[i++];
	res[j] = '\0';
	return (res);
}

