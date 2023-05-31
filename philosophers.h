/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:50:54 by nelallao          #+#    #+#             */
/*   Updated: 2023/05/31 21:40:32 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_struct
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_eat;
	int				eat_check;
	int				is_dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	m_n_eat;
	pthread_mutex_t	m_last_eat;
	pthread_mutex_t	m_eat_check;
	pthread_mutex_t	m_start_time;
}	t_struct;

typedef struct s_philo
{
	int				n_eat;
	long			start;
	int				id;
	pthread_t		philosophers;
	long			last_eat;
	t_struct		*data;
	pthread_mutex_t	m_philo;
}	t_philo;

/*LIBFT*/
int		ft_isdigit(int n);
long	ft_atoi(const char *str);
/*------------------------------*/
/*function for check arguments*/
void	ft_give_agruments(char **av, t_struct *data);
void	ft_init_mutex(t_philo	*philo, t_struct *s);
void	create_philo(t_struct *s, char **av);
void	ft_thinking(t_philo	*philo);
void	ft_taken_forks(t_philo	*philo, int right_fork, int left_fork);
void	ft_eating(t_philo	*philo);
void	ft_sleeping(t_philo	*philo);
void	*routine(void *arg);
int		ft_check_death(t_philo	*philo, t_struct *s, int i);
long	ft_t(void);
int		ft_check_arg(char **av);
void	ft_checker(t_philo	*philo, t_struct *s);
int		ft_usleep(long time);
void	ft_free(t_philo *philo, t_struct *s);

/*------------------------------*/
#endif
