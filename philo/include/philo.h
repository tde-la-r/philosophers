/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <tde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:58:17 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/05/21 17:11:39 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

# define INFINITE -42
# define T_USLEEP 128
# define STATUS_DEAD -1
# define STATUS_END -2

typedef enum e_args
{
	N_PHILO,
	T_DIE,
	T_EAT,
	T_SLEEP,
	N_MEALS,
}	t_args;

typedef struct s_lst
{
	int				status;
	pthread_mutex_t	mutex;
	struct s_lst	*next;
}					t_lst;

typedef struct s_philo
{
	int				index;
	int				*args;
	struct timeval	start;
	pthread_mutex_t	*m_print;
	t_lst			*first_fork;
	t_lst			*last_fork;
	t_lst			*condition;
}					t_philo;

typedef struct s_sim
{
	t_philo			*philos;
	t_lst			*forks;
	t_lst			*conditions;
	pthread_t		*threads;
	pthread_mutex_t	*m_print;
}					t_sim;

bool	parse_args(int argc, char **argv, int *args);
bool	init_sim(int *args, t_sim *sim);
bool	start_sim(t_philo *philos, pthread_t *threads, t_lst *conditions);
void	*philo_routine(void	*param);
bool	check_death(t_philo philo, long timestamp, long last_meal);
bool	check_end(t_lst *condition);
void	update_status(t_lst *first_fork, t_lst *last_fork, t_lst *meals);
void	set_forks_order(t_philo *philo, int *next_swap);
void	print_log(t_philo philo, long timestamp, char *msg);
int		ft_atoi(const char *nptr);
long	get_timestamp(struct timeval start);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_fprintf(int fd, const char *to_print, ...);
void	ft_lstclear(t_lst **fork, t_lst *index);
t_lst	*ft_lstlast(t_lst *lst);
void	ft_lstadd_back(t_lst **lst, t_lst *new);

#endif
