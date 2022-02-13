/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 09:35:49 by wurrigon          #+#    #+#             */
/*   Updated: 2021/10/15 09:38:33 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*tmp_d;
	char	*tmp_s;
	size_t	i;

	if (dst == NULL && src == NULL)
		return (NULL);
	tmp_d = (char *)dst;
	tmp_s = (char *)src;
	i = 0;
	if (tmp_d < tmp_s)
	{
		while (i < len)
		{
			tmp_d[i] = tmp_s[i];
			i++;
		}
	}
	else
	{
		while (len-- > 0)
			tmp_d[len] = tmp_s[len];
	}
	return ((void *)dst);
}
