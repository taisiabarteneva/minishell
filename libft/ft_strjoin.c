/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:35:51 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/19 22:10:54 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2, int free1, int free2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (s1 && s1[i])
		i++;
	while (s2 && s2[j])
		j++;
	if (!s1 && !s2)
		return (NULL);
	str = (char *)malloc((i + j + 1) * sizeof(char));
	if (str)
		str[i + j] = 0;
	while (str && s2 && j-- > 0)
		str[i + j] = s2[j];
	while (str && s1 && i-- > 0)
		str[i] = s1[i];
	if (free1 && s1)
		free((void *)s1);
	if (free2 && s1)
		free((void *)s2);
	return (str);
}
