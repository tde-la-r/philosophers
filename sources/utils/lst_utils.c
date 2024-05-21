/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_lst_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <tde-la-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:08:42 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/05/13 20:38:59 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_lstclear(t_lst **fork, t_lst *index)
{
	if (!*fork)
		return ;
	if (!index)
		index = *fork;
	if (index->next != *fork)
		ft_lstclear(fork, index->next);
	pthread_mutex_destroy(&index->mutex);
	free(index);
	*fork = NULL;
}

t_lst	*ft_lstlast(t_lst *lst)
{
	t_lst	*index;

	if (!lst)
		return (NULL);
	index = lst;
	while (index->next != lst)
		index = index->next;
	return (index);
}

void	ft_lstadd_back(t_lst **lst, t_lst *new)
{
	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
	new->next = *lst;
}
