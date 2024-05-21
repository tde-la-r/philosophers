/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:21:36 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/05/02 13:22:53 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static bool	print_argument(int fd, va_list *list, const char **arg, int *count)
{
	(*arg)++;
	if (**arg == 'i' || **arg == 'd' || **arg == 'c')
		print_integer_ptf(fd, list, **arg, count);
	else if (**arg == 'u' || **arg == 'x' || **arg == 'X')
		print_u_int_ptf(fd, list, **arg, count);
	else if (**arg == 'p')
		print_pointer_ptf(fd, list, count);
	else if (**arg == 's')
		print_string_ptf(fd, list, count);
	else if (**arg == '%')
		*count += write(fd, "%", 1);
	else if (**arg)
	{
		*count += write(fd, "%", 1);
		*count += write(fd, *arg, 1);
	}
	else
		return (false);
	return (true);
}

int	process_chars_ptf(int fd, va_list *list, const char *arg, int count)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '%')
		{
			count += write(fd, arg, i);
			arg += i;
			if (!print_argument(fd, list, &arg, &count))
				return (-1);
			arg++;
			i = 0;
			continue ;
		}
		i++;
	}
	count += write(fd, arg, i);
	return (count);
}

int	ft_fprintf(int fd, const char *to_print, ...)
{
	va_list	list;
	int		count;

	if (!to_print)
		return (-1);
	count = 0;
	va_start(list, to_print);
	count = process_chars_ptf(fd, &list, to_print, count);
	va_end(list);
	return (count);
}
