/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:50:54 by nelallao          #+#    #+#             */
/*   Updated: 2023/05/27 23:28:37 by nelallao         ###   ########.fr       */
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
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_eat;
	pthread_mutex_t	*forks;
	int				is_dead;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	m_n_eat;
	pthread_mutex_t	m_last_eat;
	int				eat_check;
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
int		t_check_arg(char **av, t_struct *s, int i);
void	ft_checker(t_philo	*philo, t_struct *s);

/*------------------------------*/
#endif
