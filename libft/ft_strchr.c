/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 09:46:30 by wurrigon          #+#    #+#             */
/*   Updated: 2022/02/10 14:23:53 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = 0;
	while (s[i] != '\0')
		i++;
	i++;
	while (tmp < i)
	{
		if ((char) c == s[tmp])
			return ((char *) &s[tmp]);
		tmp++;
	}
	return (NULL);
}