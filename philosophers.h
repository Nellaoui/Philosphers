/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:50:54 by nelallao          #+#    #+#             */
/*   Updated: 2023/05/24 17:30:55 by nelallao         ###   ########.fr       */
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
	long			start;
	pthread_mutex_t	*forks;
}	t_struct;

typedef struct s_philo
{
	int			id;
	pthread_t	philosophers;
	t_struct	*data;
}	t_philo;
/*LIBFT*/
int		ft_isdigit(int n);
long	ft_atoi(const char *str);
/*------------------------------*/
/*function for check arguments*/
int	ft_check_arg(char **av, t_struct *s, int i);
/*------------------------------*/
#endif
