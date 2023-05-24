/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:52:15 by nelallao          #+#    #+#             */
/*   Updated: 2023/05/24 18:45:29 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_time_counter(void)
{
	struct timeval	currentTime;

	gettimeofday(&currentTime, NULL);
	return ((currentTime.tv_sec * 1000) + (currentTime.tv_usec / 1000));
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		right_fork;
	int		left_fork;

	philo = (t_philo *) arg;
	// write(1, "X", 1);
	// right_fork = philo->id;
	// left_fork = (philo->id + 1) % philo->data->number_of_philosophers;
	while(1)
	{
		printf("(%ld)\n", (ft_time_counter() - philo->data->start));
	}
	return (NULL);
}

void	ft_give_agruments(char **av, t_struct *data)
{
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->number_of_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->number_of_eat = ft_atoi(av[5]);
}

void	create_philo(t_struct *s, char **av)
{
	int				i;
	t_philo			*philo;

	ft_give_agruments(av, s);

	s->forks = malloc(sizeof(pthread_mutex_t) * s->number_of_philosophers);
	philo = malloc(sizeof(t_philo) * s->number_of_philosophers);
	// philo->data = malloc(sizeof(t_philo) * s->number_of_philosophers);
	i = 0;
	while (i < s->number_of_philosophers)
		pthread_mutex_init(&s->forks[i++], NULL);
	i = 0;
	while (i < s->number_of_philosophers)
	{
		pthread_join(philo[i].philosophers, NULL);
		i++;
	}
	i = 0;
	s->start = ft_time_counter();
	while (i < s->number_of_philosophers)
	{
		philo[i].id = i;
		philo[i].data = s;
		pthread_create(&philo[i].philosophers, NULL, routine, &philo[i]);
		sleep(5);
		printf("\n\n\n\n\n\n\n");
		usleep(100);
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

	i = 0;
	if (ac == 6 || ac == 5)
	{
		// i = ft_check_arg(av, &s, ac);
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

