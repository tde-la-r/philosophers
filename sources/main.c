/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <tde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:49:13 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/05/20 15:43:25 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_philos(pthread_t *threads, int nbphilo)
{
	int	i;

	i = 0;
	while (i < nbphilo)
	{
		if (pthread_join(threads[i], NULL))
			ft_fprintf(STDERR_FILENO, "philo: pthread_join fail\n");
		i++;
	}
}

static void	clear_sim(t_sim *sim)
{
	ft_lstclear(&sim->forks, NULL);
	ft_lstclear(&sim->conditions, NULL);
	if (sim->m_print)
	{
		pthread_mutex_destroy(sim->m_print);
		free(sim->m_print);
		sim->m_print = NULL;
	}
	if (sim->philos)
		free(sim->philos);
	sim->philos = NULL;
	if (sim->threads)
		free(sim->threads);
	sim->threads = NULL;
}

int	main(int argc, char **argv)
{
	int		args[5];
	t_sim	sim;
	bool	error;

	if (argc != 5 && argc != 6)
	{
		ft_fprintf(STDERR_FILENO, "philo: argument count incorrect\n");
		return (EXIT_FAILURE);
	}
	if (parse_args(argc, argv, args))
		return (EXIT_FAILURE);
	if (init_sim(args, &sim))
	{
		clear_sim(&sim);
		return (EXIT_FAILURE);
	}
	error = start_sim(sim.philos, sim.threads, sim.conditions);
	join_philos(sim.threads, args[N_PHILO]);
	clear_sim(&sim);
	return (error);
}
