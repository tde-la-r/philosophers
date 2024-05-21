/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:06:45 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/05/03 13:55:12 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_timestamp(struct timeval start)
{
	struct timeval	time;
	unsigned int	sec_diff;
	int				usec_diff;

	gettimeofday(&time, NULL);
	sec_diff = time.tv_sec - start.tv_sec;
	usec_diff = time.tv_usec - start.tv_usec;
	if (usec_diff < 0)
		usec_diff -= 1000;
	return (sec_diff * 1000 + usec_diff / 1000);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*area1;
	unsigned char	*area2;
	size_t			i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	area1 = (void *)s1;
	area2 = (void *)s2;
	while ((area1[i] || area2[i]) && i < n)
	{
		if (area1[i] != area2[i])
			return (area1[i] - area2[i]);
		i++;
	}
	return (0);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*memory;

	if (!nmemb || !size)
	{
		memory = malloc(0);
		if (!memory)
			return (NULL);
		return (memory);
	}
	if (nmemb >= 2147483647 || size >= 2147483647)
		return (NULL);
	if (nmemb * size > 2147483647)
		return (NULL);
	memory = malloc(nmemb * size);
	if (!memory)
		return (NULL);
	memset(memory, 0, nmemb * size);
	return (memory);
}
