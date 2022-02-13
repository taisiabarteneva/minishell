/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 10:21:34 by wurrigon          #+#    #+#             */
/*   Updated: 2021/10/15 10:23:11 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char *s, unsigned int start, unsigned int len)
{
	char	*substr;
	size_t	j;
	size_t	tmp;

	j = 0;
	tmp = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		substr = (char *)malloc(ft_strlen(s) - (size_t)start + 1);
	else
		substr = (char *)malloc(len + 1);
	if (substr == NULL)
		return (NULL);
	tmp = start;
	while ((start < (tmp + len)) && (s[start]))
		substr[j++] = s[start++];
	substr[j] = '\0';
	return (substr);
}
