/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <tde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:55:36 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/05/21 17:04:29 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_sleep(t_philo philo, long last_meal)
{
	long	timestamp;
	long	last_change;
	bool	print;

	print = true;
	timestamp = get_timestamp(philo.start);
	last_change = timestamp;
	while (!check_death(philo, timestamp, last_meal))
	{
		if (print)
		{
			print_log(philo, timestamp, "is sleeping");
			print = false;
		}
		if (timestamp - last_change >= philo.args[T_SLEEP])
			return (false);
		usleep(T_USLEEP);
		timestamp = get_timestamp(philo.start);
	}
	return (true);
}

static bool	take_fork(t_lst *fork, t_philo philo, long last_meal)
{
	const int	taken = 1;
	long		timestamp;

	timestamp = get_timestamp(philo.start);
	if (check_death(philo, timestamp, last_meal))
		return (true);
	pthread_mutex_lock(&fork->mutex);
	while (fork->status == taken)
	{
		pthread_mutex_unlock(&fork->mutex);
		usleep(T_USLEEP);
		timestamp = get_timestamp(philo.start);
		if (check_death(philo, timestamp, last_meal))
			return (true);
		pthread_mutex_lock(&fork->mutex);
	}
	fork->status = taken;
	pthread_mutex_unlock(&fork->mutex);
	print_log(philo, timestamp, "has taken a fork");
	return (false);
}

static bool	philo_think(t_philo philo, long last_meal, int *next_swap)
{
	long	timestamp;

	timestamp = get_timestamp(philo.start);
	if (check_death(philo, timestamp, last_meal))
		return (true);
	print_log(philo, timestamp, "is thinking");
	set_forks_order(&philo, next_swap);
	if (take_fork(philo.first_fork, philo, last_meal))
		return (true);
	if (take_fork(philo.last_fork, philo, last_meal))
		return (true);
	return (false);
}

static bool	philo_eat(t_philo philo, long *last_meal)
{
	long	timestamp;
	bool	print;

	print = true;
	timestamp = get_timestamp(philo.start);
	while (!check_death(philo, timestamp, *last_meal))
	{
		if (print)
		{
			print_log(philo, timestamp, "is eating");
			print = false;
			*last_meal = timestamp;
		}
		if (timestamp - *last_meal >= philo.args[T_EAT])
		{
			update_status(philo.first_fork, philo.last_fork, philo.condition);
			return (false);
		}
		usleep(T_USLEEP);
		timestamp = get_timestamp(philo.start);
	}
	return (true);
}

void	*philo_routine(void	*param)
{
	t_philo	*philo;
	int		next_swap;
	long	last_meal;

	philo = (t_philo *) param;
	next_swap = 0;
	last_meal = get_timestamp(philo->start);
	while (philo->args[N_MEALS])
	{
		if (philo_think(*philo, last_meal, &next_swap))
			break ;
		if (philo_eat(*philo, &last_meal))
			break ;
		if (philo_sleep(*philo, last_meal))
			break ;
	}
	return (NULL);
}
