/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <tde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:45:52 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/05/21 17:11:12 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	str_is_only_digits(const char *str)
{
	while (ft_isdigit(*str))
		str++;
	if (*str)
		return (false);
	return (true);
}

static bool	isin_int_limit(const char *num)
{
	const int	len_int_max = 10;
	int			len;

	len = ft_strlen(num);
	if (len < len_int_max)
		return (true);
	if (len > len_int_max)
		return (false);
	if (ft_strncmp(num, "2147483647", len_int_max) > 0)
		return (false);
	return (true);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	number;

	if (!nptr[0] || !str_is_only_digits(nptr) || !isin_int_limit(nptr))
		return (-1);
	i = 0;
	sign = 1;
	number = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		number = number * 10 + nptr[i] - '0';
		i++;
	}
	return (number * sign);
}
