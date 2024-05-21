/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <tde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 19:14:06 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/05/21 17:04:21 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	end_philos(t_lst *conditions)
{
	t_lst	*index;

	index = NULL;
	while (index != conditions)
	{
		if (!index)
			index = conditions;
		pthread_mutex_lock(&index->mutex);
		index->status = STATUS_END;
		pthread_mutex_unlock(&index->mutex);
		index = index->next;
	}
}

static bool	check_meals_eaten(t_lst *already_eaten, int maxmeals)
{
	t_lst	*index;

	index = already_eaten->next;
	while (index != already_eaten)
	{
		pthread_mutex_lock(&index->mutex);
		if (index->status < maxmeals)
		{
			pthread_mutex_unlock(&index->mutex);
			return (false);
		}
		pthread_mutex_unlock(&index->mutex);
		index = index->next;
	}
	return (true);
}

static bool	supervise_philos(t_lst *conditions, int *args)
{
	int		i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&conditions->mutex);
		if (conditions->status == STATUS_DEAD)
			break ;
		if (args[N_MEALS] != INFINITE)
			if (!i && conditions->status >= args[N_MEALS])
				if (check_meals_eaten(conditions, args[N_MEALS]))
					break ;
		pthread_mutex_unlock(&conditions->mutex);
		conditions = conditions->next;
		i++;
		if (i == args[N_PHILO])
			return (false);
	}
	pthread_mutex_unlock(&conditions->mutex);
	end_philos(conditions->next);
	return (true);
}

bool	start_sim(t_philo *philos, pthread_t *threads, t_lst *conditions)
{
	int				i;
	struct timeval	start;

	i = 0;
	gettimeofday(&start, NULL);
	while (i < (*philos).args[N_PHILO])
	{
		philos[i].start = start;
		if (pthread_create(&threads[i], NULL, philo_routine, &philos[i]))
		{
			ft_fprintf(STDERR_FILENO, "philo: pthread_create fail\n");
			end_philos(conditions);
			return (true);
		}
		usleep(50);
		i++;
	}
	while (!supervise_philos(conditions, philos->args))
		usleep(T_USLEEP);
	return (false);
}
