/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:52:15 by nelallao          #+#    #+#             */
/*   Updated: 2023/05/31 23:30:07 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_give_agruments(char **av, t_struct *data)
{
	data->num_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->number_of_eat = ft_atoi(av[5]);
}

void	ft_init_mutex(t_philo *philo, t_struct *s)
{
	int	i;

	i = 0;
	while (i < s->num_of_philo)
	{
		pthread_mutex_init(&s->forks[i], NULL);
		pthread_mutex_init(&philo[i].m_philo, NULL);
		i++;
	}
	pthread_mutex_init(&s->m_last_eat, NULL);
	pthread_mutex_init(&s->m_dead, NULL);
	pthread_mutex_init(&s->m_n_eat, NULL);
	pthread_mutex_init(&s->m_eat_check, NULL);
	pthread_mutex_init(&s->m_start_time, NULL);
}

void	create_philo(t_struct *s, char **av)
{
	int				i;
	t_philo			*philo;

	ft_give_agruments(av, s);
	s->forks = malloc(sizeof(pthread_mutex_t) * s->num_of_philo);
	philo = malloc(sizeof(t_philo) * s->num_of_philo);
	ft_init_mutex(philo, s);
	i = 0;
	while (i < s->num_of_philo)
	{
		philo[i].id = i;
		philo[i].data = s;
		philo[i].n_eat = 0;
		pthread_create(&philo[i].philosophers, NULL, routine, &philo[i]);
		usleep(20);
		i++;
	}
	ft_checker(philo, s);
	ft_free(philo, s);
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
		if (!ft_check_arg(av))
		{
			write(2, "Please enter a valid numbers\n", 28);
			free(s);
			return (0);
		}
		create_philo(s, av);
	}
	else
	{
		free(s);
		write(2, "MISSING ARGUMENTS : Arguments must be (5) or (4)\n", 49);
	}
}
