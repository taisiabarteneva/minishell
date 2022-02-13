/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 10:02:26 by wurrigon          #+#    #+#             */
/*   Updated: 2021/10/15 10:04:19 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	unsigned int	i;
	char			*mod;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	mod = (char *)malloc(len + 1);
	if (mod == NULL)
		return (NULL);
	while (i < len)
	{
		mod[i] = f(i, s[i]);
		i++;
	}
	mod[i] = '\0';
	return (mod);
}
