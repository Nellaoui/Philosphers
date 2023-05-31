/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:05:32 by nelallao          #+#    #+#             */
/*   Updated: 2023/05/31 23:30:45 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int n)
{
	if (n >= '0' && n <= '9')
		return (1);
	else
		return (0);
}

long	ft_atoi(const char *str)
{
	long	signe;
	long	i;
	long	result;

	signe = 1;
	i = 0;
	result = 0;
	if (str[i] == '-')
	{
		signe = signe * (-1);
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * signe);
}

long	ft_t(void)
{
	struct timeval	currentime;

	gettimeofday(&currentime, NULL);
	return ((currentime.tv_sec * 1000) + (currentime.tv_usec / 1000));
}

int	ft_usleep(long time)
{
	long	start;

	start = ft_t();
	while ((ft_t() - start) < time)
		usleep(85);
	return (0);
}

void	ft_free(t_philo *philo, t_struct *s)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&s->m_last_eat);
	pthread_mutex_destroy(&s->m_dead);
	pthread_mutex_destroy(&s->m_n_eat);
	pthread_mutex_destroy(&s->m_eat_check);
	pthread_mutex_destroy(&s->m_start_time);
	pthread_mutex_destroy(s->forks);
	while (i < s->num_of_philo)
	{
		free(philo[i].data);
		pthread_mutex_destroy(&philo[i].m_philo);
		i++;
	}
	free(s->forks);
	free(philo);
}
