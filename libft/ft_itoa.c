/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:41:18 by wurrigon          #+#    #+#             */
/*   Updated: 2021/10/15 11:52:17 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*reverse(char *buffer, int i, int j)
{
	char	t;

	while (i < j)
	{
		t = buffer[i];
		buffer[i] = buffer[j];
		buffer[j] = t;
		i++;
		j--;
	}
	return (buffer);
}

static int	ft_itoa_count_len(long val)
{
	int	i;

	i = 0;
	if (val < 0)
		val = val * (-1);
	while (val >= 1)
	{
		i++;
		val = val / 10;
		if (val >= 0 && val <= 9)
		{
			i++;
			break ;
		}
	}
	return (i);
}

char	*ft_itoa_null_case(void)
{
	char	*str;

	str = (char *)malloc(2);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

char	*ft_itoa_convert(long size, char *str)
{
	int	rmd;
	int	j;

	j = 0;
	if (size < 0)
	{
		size = size * (-1);
		str[j] = '-';
		j++;
	}
	while (size >= 1)
	{
		rmd = size % 10;
		if (rmd >= 10)
			str[j++] = 65 + (rmd + 10);
		str[j++] = 48 + rmd;
		size = size / 10;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int		len;
	int		i;
	long	size;
	char	*str;

	size = n;
	if (size == 0 || size == -0)
		return (ft_itoa_null_case());
	len = ft_itoa_count_len(size);
	str = (char *)malloc(len + 2);
	if (str == NULL)
		return (NULL);
	ft_itoa_convert(size, str);
	i = ft_strlen(str);
	if (str[0] == '-')
		str = reverse(str, 1, i - 1);
	else
		str = reverse(str, 0, i - 1);
	return (str);
}
