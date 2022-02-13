/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:39:06 by wurrigon          #+#    #+#             */
/*   Updated: 2021/10/15 13:40:53 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstl;
	size_t	srcl;
	size_t	i;
	size_t	j;

	dstl = ft_strlen(dst);
	srcl = ft_strlen(src);
	if (size == 0)
		return (srcl);
	j = 0;
	i = dstl;
	if (dstl < size - 1 && size > 0)
	{
		while (src[j] && dstl + j < size - 1)
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		dst[i] = '\0';
	}
	if (size < dstl)
		return (srcl + size);
	return (dstl + srcl);
}
