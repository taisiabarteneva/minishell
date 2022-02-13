/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 18:44:49 by wurrigon          #+#    #+#             */
/*   Updated: 2022/02/10 14:23:47 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	ch;
	size_t			i;
	char			*tmp;

	ch = (unsigned char) c;
	i = 0;
	tmp = (char *)b;
	while (i < len)
	{
		*(tmp + i) = ch;
		i++;
	}
	return (b);
}