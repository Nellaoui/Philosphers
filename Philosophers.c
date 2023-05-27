/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:52:15 by nelallao          #+#    #+#             */
/*   Updated: 2023/05/27 23:46:13 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


long	ft_time_counter(void)
{
	struct timeval	currentTime;

	gettimeofday(&currentTime, NULL);
	return ((currentTime.tv_sec * 1000) + (currentTime.tv_usec / 1000));
}

void	ft_thinking(t_philo	*philo)
{
		pthread_mutex_lock(&philo->data->m_dead);
		if (philo->data->is_dead == 0 && philo->data->number_of_eat >= philo->data->eat_check)
			printf("%ld %d is thinking \n", (ft_time_counter() - philo->start), philo->id + 1);
		pthread_mutex_unlock(&philo->data->m_dead);

}

void	ft_taken_forks(t_philo	*philo)
{
	int		right_fork;
	int		left_fork;

	right_fork = philo->id;
	left_fork = (philo->id + 1) % philo->data->number_of_philosophers;
		pthread_mutex_lock(&philo->data->forks[right_fork]);
		pthread_mutex_lock(&philo->data->m_dead);
		if (philo->data->is_dead == 0 && philo->data->number_of_eat >= philo->data->eat_check)
			printf("%ld %d has taken a fork\n", (ft_time_counter() - philo->start), philo->id + 1);
		pthread_mutex_unlock(&philo->data->m_dead);
		pthread_mutex_lock(&philo->data->forks[left_fork]);
		pthread_mutex_lock(&philo->data->m_dead);
		if (philo->data->is_dead == 0 && philo->data->number_of_eat >= philo->data->eat_check)
			printf("%ld %d has taken a fork\n", (ft_time_counter() - philo->start), philo->id + 1);
		pthread_mutex_unlock(&philo->data->m_dead);

}

void	ft_eating(t_philo	*philo)
{
	int		right_fork;
	int		left_fork;

	right_fork = philo->id;
	left_fork = (philo->id + 1) % philo->data->number_of_philosophers;
		pthread_mutex_lock(&philo->data->m_dead);
		if (philo->data->is_dead == 0 && philo->data->number_of_eat >= philo->data->eat_check)
		{
			printf("%ld %d is eating\n", (ft_time_counter() - philo->start), philo->id + 1);
			pthread_mutex_lock(&philo->data->m_n_eat);
			philo->n_eat++;
			pthread_mutex_unlock(&philo->data->m_n_eat);
		}
		pthread_mutex_unlock(&philo->data->m_dead);
		pthread_mutex_lock(&philo->data->m_last_eat);
		philo->last_eat = ft_time_counter();
		pthread_mutex_unlock(&philo->data->m_last_eat);
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->data->forks[right_fork]);
		pthread_mutex_unlock(&philo->data->forks[left_fork]);
}

void	ft_sleeping(t_philo	*philo)
{
		pthread_mutex_lock(&philo->data->m_dead);
		if (philo->data->is_dead == 0 && philo->data->number_of_eat >= philo->data->eat_check)
			printf("%ld %d is sleeping\n", (ft_time_counter() - philo->start), philo->id+1);
		pthread_mutex_unlock(&philo->data->m_dead);
		usleep(philo->data->time_to_sleep * 1000);
		pthread_mutex_lock(&philo->data->m_n_eat);
		if (philo->n_eat == philo->data->number_of_eat)
			philo->data->eat_check++;
		pthread_mutex_unlock(&philo->data->m_n_eat);

}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	philo->start = ft_time_counter();
	pthread_mutex_lock(&philo->data->m_last_eat);
	philo->last_eat = ft_time_counter();
	pthread_mutex_unlock(&philo->data->m_last_eat);
	if ((philo->id % 2) == 0)
		usleep(1000);
	while (1)
	{
		if (philo->data->is_dead == 2)
			return NULL;
		ft_thinking(philo);
		ft_taken_forks(philo);
		ft_eating(philo);
		ft_sleeping(philo);
	}
	return (NULL);
}

void	ft_give_agruments(char **av, t_struct *data)
{
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->number_of_eat = ft_atoi(av[5]);
	// data->start = ft_time_counter();
}

void	ft_init_mutex(t_philo	*philo, t_struct *s)
{
	int	i;
	i = 0;
	while (i < s->number_of_philosophers)
	{
		pthread_mutex_init(&s->forks[i], NULL);
		pthread_mutex_init(&philo[i].m_philo, NULL);
		i++;
	}
	pthread_mutex_init(&s->m_last_eat, NULL);
	pthread_mutex_init(&s->m_dead, NULL);
	pthread_mutex_init(&s->m_n_eat, NULL);
}
void	create_philo(t_struct *s, char **av)
{
	int				i;
	t_philo			*philo;

	ft_give_agruments(av, s);
	s->forks = malloc(sizeof(pthread_mutex_t) * s->number_of_philosophers);
	philo = malloc(sizeof(t_philo) * s->number_of_philosophers);
	ft_init_mutex(philo, s);
	i = 0;
	while (i < s->number_of_philosophers)
	{
		philo[i].id = i;
		philo[i].data = s;
		philo[i].n_eat = 0;
		pthread_create(&philo[i].philosophers, NULL, routine, &philo[i]);
		usleep(100);
		i++;
	}
	ft_checker(philo, s);
}

void	ft_checker(t_philo	*philo, t_struct *s)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < s->number_of_philosophers)
		{
			pthread_mutex_lock(&philo->data->m_last_eat);
			if ((ft_time_counter() - philo[i].last_eat) >= philo->data->time_to_die)
			{
				pthread_mutex_lock(&s->m_dead);
				printf("%ld %d died	\n", (ft_time_counter() - philo[i].start), philo[i].id + 1);
				s->is_dead = 1;
				pthread_mutex_unlock(&s->m_dead);
				pthread_mutex_unlock(&philo->data->m_last_eat);
				return ;
			}
			if (philo[i].data->eat_check == philo[i].data->number_of_philosophers)
			{
				philo[i].data->is_dead = 2;
				return ;
			}
			i++;
			pthread_mutex_unlock(&philo->data->m_last_eat);
		}
		usleep(1000);
	}
	i = 0;
	while (i < s->number_of_philosophers)
	{
		pthread_join(philo[i].philosophers, NULL);
		i++;
	}

}

int	ft_check_arg(char **av, t_struct *s, int ac)
{
	int	j;
	int	i;

	j = 1;
	while (av[j])
	{
		i = 0;
		while (av[j][i])
		{
			if (!ft_isdigit(av[j][i]))
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	int			i;
	t_struct	*s;

	s = malloc(sizeof(t_struct));
	s->is_dead = 0;
	i = 0;
	if (ac == 6 || ac == 5)
	{
		// if (!ft_check_arg(av, &s, ac))
		// {
		// 	write(2, "Please enter a valid numbers\n", 28);
		// 	return (0);
		// }
		create_philo(s, av);
	}
	else
		write(2, "MISSING ARGUMENTS : Arguments must be (5) or (4)\n", 49);
}

