/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 18:45:46 by wurrigon          #+#    #+#             */
/*   Updated: 2021/10/15 09:35:21 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int		i;
	char	*tmp_d;
	char	*tmp_s;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	tmp_d = (char *)dst;
	tmp_s = (char *)src;
	while (n--)
	{
		tmp_d[i] = tmp_s[i];
		i++;
	}
	return ((void *)dst);
}
