/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:14:11 by jcauchet          #+#    #+#             */
/*   Updated: 2022/06/04 12:03:11 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	error(void)
{
	write(1, "Error\n", 6);
	return (EXIT_FAILURE);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -sign;
	if ((str[i - 1] == '-' || str[i - 1] == '+') && !str[i])
		return (-1);
	while (str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (-1);
		else
			result = result * 10 + str[i++] - '0';
	}
	if ((sign * result < -2147483648) || (sign * result > 2147483647))
		return (-1);
	return (sign * result);
}
