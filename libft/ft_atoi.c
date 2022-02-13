/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 09:11:40 by wurrigon          #+#    #+#             */
/*   Updated: 2022/02/13 22:22:45 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



int	ft_atoi(const char *str)
{
	long	val;
	int		sign;

	val = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		val = val * 10 + *str - '0';
		if (val > 2147483648 && sign == -1)
			return (0);
		else if (val > 2147483648)
			return (-1);
		str++;
	}
	return (val * sign);
}
