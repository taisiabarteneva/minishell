/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 10:04:56 by wurrigon          #+#    #+#             */
/*   Updated: 2021/10/15 10:06:30 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*arr1;
	unsigned char	*arr2;

	i = 0;
	arr1 = (unsigned char *) s1;
	arr2 = (unsigned char *) s2;
	while (n--)
	{
		if ((arr1[i] != arr2[i])
			|| arr1[i] == '\0'
			|| arr2[i] == '\0')
			return (arr1[i] - arr2[i]);
		i++;
	}
	return (0);
}
