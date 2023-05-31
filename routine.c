/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:10:57 by nelallao          #+#    #+#             */
/*   Updated: 2023/05/31 18:38:25 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_thinking(t_philo	*philo)
{
	pthread_mutex_lock(&philo->data->m_dead);
	pthread_mutex_lock(&philo->data->m_eat_check);
	pthread_mutex_lock(&philo->data->m_start_time);
	if (philo->data->is_dead == 0
		&& philo->data->number_of_eat >= philo->data->eat_check)
		printf("%ld %d is thinking\n", (ft_t() - philo->start), philo->id + 1);
	pthread_mutex_unlock(&philo->data->m_start_time);
	pthread_mutex_unlock(&philo->data->m_eat_check);
	pthread_mutex_unlock(&philo->data->m_dead);
}

void	ft_taken_forks(t_philo	*philo, int right_fork, int left_fork)
{
	pthread_mutex_lock(&philo->data->forks[right_fork]);
	pthread_mutex_lock(&philo->data->m_dead);
	pthread_mutex_lock(&philo->data->m_eat_check);
	pthread_mutex_lock(&philo->data->m_start_time);
	if (philo->data->is_dead == 0
		&& philo->data->number_of_eat >= philo->data->eat_check)
		printf("%ld %d has taken a fork\n",
			(ft_t() - philo->start), philo->id + 1);
	pthread_mutex_unlock(&philo->data->m_start_time);
	pthread_mutex_unlock(&philo->data->m_eat_check);
	pthread_mutex_unlock(&philo->data->m_dead);
	pthread_mutex_lock(&philo->data->forks[left_fork]);
	pthread_mutex_lock(&philo->data->m_dead);
	pthread_mutex_lock(&philo->data->m_eat_check);
	pthread_mutex_lock(&philo->data->m_start_time);
	if (philo->data->is_dead == 0
		&& philo->data->number_of_eat >= philo->data->eat_check)
		printf("%ld %d has taken a fork\n",
			(ft_t() - philo->start), philo->id + 1);
	pthread_mutex_unlock(&philo->data->m_start_time);
	pthread_mutex_unlock(&philo->data->m_eat_check);
	pthread_mutex_unlock(&philo->data->m_dead);
}

void	ft_eating(t_philo	*philo)
{
	int		right_fork;
	int		left_fork;

	right_fork = philo->id;
	left_fork = (philo->id + 1) % philo->data->num_of_philo;
	pthread_mutex_lock(&philo->data->m_dead);
	pthread_mutex_lock(&philo->data->m_eat_check);
	pthread_mutex_lock(&philo->data->m_start_time);
	if (philo->data->is_dead == 0
		&& philo->data->number_of_eat >= philo->data->eat_check)
	{
		printf("%ld %d is eating\n", (ft_t() - philo->start), philo->id + 1);
		pthread_mutex_lock(&philo->data->m_n_eat);
		philo->n_eat++;
		pthread_mutex_unlock(&philo->data->m_n_eat);
	}
	pthread_mutex_unlock(&philo->data->m_start_time);
	pthread_mutex_unlock(&philo->data->m_eat_check);
	pthread_mutex_unlock(&philo->data->m_dead);
	pthread_mutex_lock(&philo->data->m_last_eat);
	philo->last_eat = ft_t();
	pthread_mutex_unlock(&philo->data->m_last_eat);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[right_fork]);
	pthread_mutex_unlock(&philo->data->forks[left_fork]);
}

void	ft_sleeping(t_philo	*philo)
{
	pthread_mutex_lock(&philo->data->m_dead);
	pthread_mutex_lock(&philo->data->m_eat_check);
	pthread_mutex_lock(&philo->data->m_start_time);
	if (philo->data->is_dead == 0
		&& philo->data->number_of_eat >= philo->data->eat_check)
		printf("%ld %d is sleeping\n", (ft_t() - philo->start), philo->id + 1);
	pthread_mutex_unlock(&philo->data->m_start_time);
	pthread_mutex_unlock(&philo->data->m_eat_check);
	pthread_mutex_unlock(&philo->data->m_dead);
	ft_usleep(philo->data->time_to_sleep);
	pthread_mutex_lock(&philo->data->m_n_eat);
	if (philo->n_eat == philo->data->number_of_eat)
	{
		pthread_mutex_lock(&philo->data->m_eat_check);
		pthread_mutex_unlock(&philo->data->m_eat_check);
		philo->data->eat_check++;
	}
	pthread_mutex_unlock(&philo->data->m_n_eat);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		right_fork;
	int		left_fork;

	philo = (t_philo *) arg;
	right_fork = philo->id;
	left_fork = (philo->id + 1) % philo->data->num_of_philo;
	pthread_mutex_lock(&philo->data->m_start_time);
	philo->start = ft_t();
	pthread_mutex_unlock(&philo->data->m_start_time);
	pthread_mutex_lock(&philo->data->m_last_eat);
	philo->last_eat = ft_t();
	pthread_mutex_unlock(&philo->data->m_last_eat);
	while (1)
	{
		pthread_mutex_lock(&philo->data->m_dead);
		if (philo->data->is_dead == 2)
			return (NULL);
		pthread_mutex_unlock(&philo->data->m_dead);
		ft_thinking(philo);
		ft_taken_forks(philo, right_fork, left_fork);
		ft_eating(philo);
		ft_sleeping(philo);
	}
	return (NULL);
}
