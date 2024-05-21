/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <tde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:55:40 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/05/20 16:01:57 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*str_arg(int arg)
{
	if (arg == N_PHILO)
		return ("number_of_philosophers");
	if (arg == T_DIE)
		return ("time_to_die");
	if (arg == T_EAT)
		return ("time_to_eat");
	if (arg == T_SLEEP)
		return ("time_to_sleep");
	if (arg == N_MEALS)
		return ("number_of_times_each_philosopher_must_eat");
	return (NULL);
}

static bool	print_err_msg(int argc, int *args)
{
	bool	error;
	int		i;

	error = false;
	i = 0;
	while (i < argc - 1)
	{
		if (args[i] == -1)
		{
			ft_fprintf(STDERR_FILENO, "philo: %s wrong argument\n", str_arg(i));
			error = true;
		}
		else if (i == N_PHILO && args[N_PHILO] == 0)
		{
			ft_fprintf(STDERR_FILENO, "philo: %s wrong argument\n", str_arg(i));
			error = true;
		}
		i++;
	}
	return (error);
}

bool	parse_args(int argc, char **argv, int *args)
{
	args[N_PHILO] = ft_atoi(argv[1]);
	args[T_DIE] = ft_atoi(argv[2]);
	args[T_EAT] = ft_atoi(argv[3]);
	args[T_SLEEP] = ft_atoi(argv[4]);
	if (argv[5])
		args[N_MEALS] = ft_atoi(argv[5]);
	else
		args[N_MEALS] = INFINITE;
	if (print_err_msg(argc, args))
		return (true);
	return (false);
}
