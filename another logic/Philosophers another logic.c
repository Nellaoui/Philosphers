/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:52:15 by nelallao          #+#    #+#             */
/*   Updated: 2023/05/24 17:02:22 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_time_counter(void)
{
	struct timeval	currentTime;

	return ((currentTime.tv_sec * 1000) + currentTime.tv_usec / 1000);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	// philo->data->start = ft_time_counter();
	philo = (t_philo *) arg;
	// right_fork = philo->id;
	// left_fork = (philo->id + 1) % philo->data->number_of_philosophers;
	// while(1)
	// {
		printf("%ld Philosopher is thinking\n", ft_time_counter());
		// printf("%ld Philosopher is thinking\n", (ft_time_counter() - philo->data->start));
		// printf("%ld Philosopher is thinking\n", (ft_time_counter() - philo->data->start));
	// }
	return (NULL);
}

void	create_philo(char **av)
{
	int				i;
	t_philo 		*ph;
	pthread_t		*th;
	pthread_mutex_t	*forks;
	long	t;
	// t_philo			*philo;

	ph->number_of_philosophers = ft_atoi(av[1]);
	ph->time_to_die = ft_atoi(av[2]);
	ph->number_of_eat = ft_atoi(av[3]);
	ph->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		ph->number_of_eat = ft_atoi(av[5]);
	// ph->forks = malloc(sizeof(pthread_mutex_t) * ph->number_of_philosophers);
	ph = malloc(sizeof(t_philo) * ph->number_of_philosophers);
	th = malloc(sizeof(pthread_t) * ph->number_of_philosophers);
	forks = malloc(sizeof(pthread_mutex_t) * ph->number_of_philosophers);
	// ph[0].data = malloc(sizeof(t_philo) * s->number_of_philosophers);
	// i = 0;
	// while (i < s->number_of_philosophers)
	// {
	// 	ph[i].data = philo[0].data;
	// 	i++;
	// }
	// printf("here\n");
	// i = 0;
	// while (i < s->number_of_philosophers)
	// {
	// 	printf("philo %p\n", &philo[i]);
	// 	printf("%p\n", &philo[i].data);
	// 	i++;
	// }
	i = 0;
	while (i < ph->number_of_philosophers)
		pthread_mutex_init(&forks[i++], NULL);
	i = 0;
	t = ft_time_counter();
	while (i < ph->number_of_philosophers)
	{
		ph[i].id = i;
		ph[i].start_time = t;
		ph[i].right_fork = &forks[i];
		ph[i].left_fork = &forks[(i + 1) % ph->number_of_philosophers];
		pthread_create(&th[i], NULL, routine, &ph[i]);
		usleep(100);
		i++;
	}
	i = 0;
	while (i < ph->number_of_philosophers)
	{
		pthread_join(th[i], NULL);
		i++;
	}
}

int	ft_check_arg(char **av, int ac)
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
	int				i;
	t_philo			*ph;


	i = 0;
	if (ac == 6 || ac == 5)
	{
		if (!ft_check_arg(av, ac))
		{
			write(2, "Please enter a valid numbers\n", 28);
			return (0);
		}
		create_philo(av);
	}
	else
		write(2, "MISSING ARGUMENTS : Arguments must be (5) or (4)\n", 49);
}

