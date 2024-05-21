/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <tde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:18:11 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/05/21 17:42:14 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_end(t_lst *condition)
{
	pthread_mutex_lock(&condition->mutex);
	if (condition->status == STATUS_END)
	{
		pthread_mutex_unlock(&condition->mutex);
		return (true);
	}
	pthread_mutex_unlock(&condition->mutex);
	return (false);
}

bool	check_death(t_philo philo, long timestamp, long last_meal)
{
	if (check_end(philo.condition))
		return (true);
	if (timestamp - last_meal < philo.args[T_DIE])
		return (false);
	pthread_mutex_lock(philo.m_print);
	if (!check_end(philo.condition))
	{
		pthread_mutex_lock(&philo.condition->mutex);
		philo.condition->status = STATUS_DEAD;
		pthread_mutex_unlock(&philo.condition->mutex);
		printf("%ld\t%d died\n", timestamp, philo.index);
		pthread_mutex_lock(&philo.condition->mutex);
		while (philo.condition->status != STATUS_END)
		{
			pthread_mutex_unlock(&philo.condition->mutex);
			usleep(T_USLEEP);
			pthread_mutex_lock(&philo.condition->mutex);
		}
		pthread_mutex_unlock(&philo.condition->mutex);
	}
	pthread_mutex_unlock(philo.m_print);
	return (true);
}

void	print_log(t_philo philo, long timestamp, char *msg)
{
	pthread_mutex_lock(philo.m_print);
	if (!check_end(philo.condition))
		printf("%ld\t%d %s\n", timestamp, philo.index, msg);
	pthread_mutex_unlock(philo.m_print);
}

void	update_status(t_lst *first_fork, t_lst *last_fork, t_lst *meals)
{
	const int	available = 0;

	pthread_mutex_lock(&first_fork->mutex);
	first_fork->status = available;
	pthread_mutex_unlock(&first_fork->mutex);
	pthread_mutex_lock(&last_fork->mutex);
	last_fork->status = available;
	pthread_mutex_unlock(&last_fork->mutex);
	pthread_mutex_lock(&meals->mutex);
	if (meals->status != STATUS_END)
		meals->status++;
	pthread_mutex_unlock(&meals->mutex);
}

void	set_forks_order(t_philo *philo, int *next_swap)
{
	t_lst		*tmp;

	if (!(philo->args[N_PHILO] & 1) || philo->index & 1)
		return ;
	if (!*next_swap)
		*next_swap = (philo->index / 2) % (philo->args[N_PHILO] / 2);
	pthread_mutex_lock(&philo->condition->mutex);
	if (philo->condition->status != *next_swap)
	{
		pthread_mutex_unlock(&philo->condition->mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->condition->mutex);
	tmp = philo->first_fork;
	philo->first_fork = philo->last_fork;
	philo->last_fork = tmp;
	*next_swap += philo->args[N_PHILO] / 2;
}
