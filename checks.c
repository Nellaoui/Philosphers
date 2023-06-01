/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:12:56 by nelallao          #+#    #+#             */
/*   Updated: 2023/06/01 13:08:42 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_check_arg(char **av)
{
	int	j;
	int	i;

	j = 1;
	while (av[j])
	{
		i = 0;
		while (av[j][i] == '0')
			i++;
		if (av[j][i] == '\0')
			return (0);
		while (av[j][i] != '\0')
		{
			if (!ft_isdigit(av[j][i]))
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

void	ft_checker(t_philo	*philo, t_struct *s)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < s->num_of_philo)
		{
			if (ft_check_death(philo, s, i) == 3)
				return ;
			if (philo[i].data->eat_check == philo[i].data->num_of_philo)
			{
				philo[i].data->is_dead = 2;
				return ;
			}
			i++;
		}
	}
	i = 0;
	while (i < s->num_of_philo)
		pthread_join(philo[i++].philosophers, NULL);
}

int	ft_check_death(t_philo	*philo, t_struct *s, int i)
{
	pthread_mutex_lock(&philo->data->m_last_eat);
	if (((ft_t() - philo[i].last_eat) > philo->data->time_to_die)
		&& philo[i].last_eat != 0)
	{
		pthread_mutex_lock(&s->m_dead);
		pthread_mutex_lock(&s->m_start_time);
		printf("%ld %d died\n", (ft_t() - philo[i].start), philo[i].id + 1);
		s->is_dead = 1;
		pthread_mutex_unlock(&s->m_start_time);
		pthread_mutex_unlock(&s->m_dead);
		pthread_mutex_unlock(&philo->data->m_last_eat);
		return (3);
	}
	pthread_mutex_unlock(&philo->data->m_last_eat);
	return (1);
}
