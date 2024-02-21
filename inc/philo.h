/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:44:12 by atudor            #+#    #+#             */
/*   Updated: 2024/02/07 17:44:54 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
#include "../inc/libft/libft.h"

typedef struct s_global
{
	int				nr_ph;
	int				die_time;
	int 			eat_time;
	int 			sleep_time;
	int 			nr_must_eat;
	long			tm_begin;
	struct s_philo	*philosophers;
	int				someone_died;
	pthread_mutex_t	mtx_print;
	pthread_mutex_t mtx_global;
	pthread_mutex_t	mtx_for_death;
	pthread_mutex_t mtx_for_fullness;
} t_global;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				times_eaten;
	int				i_am_full;
	long			last_time_eaten;
	pthread_mutex_t mtx_last_tm_eat;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;
	t_global		*global;
} t_philo;

int		wrong_args(int argc, char **argv, t_global *global);
void	init_philo(t_global *global, t_philo *philo);
void	print_str(t_philo philo, char *str);
void	*philo_routine(void *arg);
int	god(t_philo *philo, t_global *global);
void	init_thread(t_global *global, t_philo *philo);
long	ft_get_time(long time_start);
void	ft_usleep(long long time);


# endif
