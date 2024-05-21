/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <tde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:56:20 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/05/20 16:01:10 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*create_array(size_t size, int nbphilo)
{
	void	*array;

	array = ft_calloc(size, nbphilo);
	if (!array)
		ft_fprintf(STDERR_FILENO, "philo: malloc fail\n");
	return (array);
}

static void	init_philos(t_philo *philos, int i, int *args, t_sim sim)
{
	if (i & 1)
	{
		philos[i].first_fork = sim.forks;
		philos[i].last_fork = sim.forks->next;
	}
	else
	{
		philos[i].first_fork = sim.forks->next;
		philos[i].last_fork = sim.forks;
	}
	philos[i].condition = sim.conditions;
	philos[i].args = args;
	philos[i].index = i + 1;
	philos[i].m_print = sim.m_print;
	sim.conditions = sim.conditions->next;
	sim.forks = sim.forks->next;
	if (i + 1 < args[N_PHILO])
		init_philos(philos, i + 1, args, sim);
}

static void	ft_lstnew(int index, int nbphilo, t_lst **lst)
{
	t_lst	*new;

	new = ft_calloc(sizeof(t_lst), 1);
	if (!new)
	{
		ft_fprintf(STDERR_FILENO, "philo: malloc fail\n");
		ft_lstclear(lst, NULL);
		return ;
	}
	if (pthread_mutex_init(&new->mutex, NULL))
	{
		ft_fprintf(STDERR_FILENO, "philo: pthread_mutex_init fail\n");
		ft_lstclear(lst, NULL);
		free(new);
		return ;
	}
	ft_lstadd_back(lst, new);
	if (index < nbphilo)
		ft_lstnew(index + 1, nbphilo, lst);
}

static bool	create_mutex_ptr(t_sim *sim)
{
	sim->m_print = malloc(sizeof(pthread_mutex_t));
	if (!sim->m_print)
	{
		ft_fprintf(STDERR_FILENO, "philo: malloc fail\n");
		return (true);
	}
	if (pthread_mutex_init(sim->m_print, NULL))
	{
		ft_fprintf(STDERR_FILENO, "philo: pthread_mutex_init fail\n");
		free(sim->m_print);
		sim->m_print = NULL;
		return (true);
	}
	return (false);
}

bool	init_sim(int *args, t_sim *sim)
{
	memset(sim, 0, sizeof(t_sim));
	ft_lstnew(1, args[N_PHILO], &sim->forks);
	ft_lstnew(1, args[N_PHILO], &sim->conditions);
	if (!sim->forks || !sim->conditions)
		return (true);
	sim->philos = create_array(sizeof(t_philo), args[N_PHILO]);
	if (!sim->philos)
		return (true);
	if (create_mutex_ptr(sim))
		return (true);
	init_philos(sim->philos, 0, args, *sim);
	sim->threads = create_array(sizeof(pthread_t), args[N_PHILO]);
	if (!sim->threads)
		return (true);
	return (false);
}
