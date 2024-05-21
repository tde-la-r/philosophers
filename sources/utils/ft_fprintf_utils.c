/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:05:18 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/05/01 18:49:11 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_number(unsigned long nbr, char *base, char *to_print, int *i)
{
	size_t	len;

	len = ft_strlen(base);
	if (nbr > len - 1)
		get_number(nbr / len, base, to_print, i);
	to_print[*i] = base[nbr % len];
	(*i)++;
}

void	print_string_ptf(int fd, va_list *list, int *count)
{
	char	*str;
	size_t	len;

	str = va_arg(*list, char *);
	if (str)
	{
		len = ft_strlen(str);
		*count += write(fd, str, len);
	}
	else
		*count += write(fd, "(null)", 6);
}

void	print_integer_ptf(int fd, va_list *list, const char arg, int *count)
{
	int		integer;
	int		i;
	char	to_print[10];

	integer = va_arg(*list, int);
	if (arg == 'c')
	{
		*count += write(fd, &integer, 1);
		return ;
	}
	if (integer == INT_MIN)
	{
		*count += write(fd, "-2147483648", 11);
		return ;
	}
	if (integer < 0)
	{
		integer = -integer;
		*count += write (fd, "-", 1);
	}
	i = 0;
	get_number(integer, "0123456789", to_print, &i);
	*count += write(fd, to_print, i);
}

void	print_u_int_ptf(int fd, va_list *list, const char arg, int *count)
{
	unsigned int	u_integer;
	int				i;
	char			to_print[16];

	u_integer = va_arg(*list, unsigned int);
	i = 0;
	if (arg == 'x')
		get_number(u_integer, "0123456789abcdef", to_print, &i);
	if (arg == 'X')
		get_number(u_integer, "0123456789ABCDEF", to_print, &i);
	if (arg == 'u')
		get_number(u_integer, "0123456789", to_print, &i);
	*count += write(fd, to_print, i);
}

void	print_pointer_ptf(int fd, va_list *list, int *count)
{
	unsigned long	ptr;
	int				i;
	char			to_print[16];

	ptr = va_arg(*list, unsigned long);
	if (ptr)
	{
		*count += write (fd, "0x", 2);
		i = 0;
		get_number(ptr, "0123456789abcdef", to_print, &i);
		*count += write(fd, to_print, i);
	}
	else
		*count += write(fd, "(nil)", 5);
}
