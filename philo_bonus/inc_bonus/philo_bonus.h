/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:14:33 by atudor            #+#    #+#             */
/*   Updated: 2024/02/28 20:14:40 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/queue.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
#include <signal.h>

typedef struct s_global
{
	int				nr_ph;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				nr_must_eat;
	long			tm_begin;
	struct s_philo	*philosophers;
	sem_t	*print;
	sem_t	*death;
	sem_t	*forks;
}	t_global;

typedef struct s_philo
{
	pid_t			pid;
	int				id;
	int				times_eaten;
	int				i_am_full;
	long			last_time_eaten;
	t_global		*global;
}	t_philo;


//inits

void	philo_routine(t_global *global, t_philo *philo, sem_t *forks);
void	init_philo(t_global *global, t_philo *philo);
void	init_process(t_global *global, t_philo *philo, sem_t *forks);

//check_args

int			ft_isdigit(char c);
long long	ft_atoi(char *str);
int			check_digit(int argc, char **argv);
void		fill_args(int argc, char **argv, t_global *global);
int			wrong_args(int argc, char **argv, t_global *global);

//utils

long	ft_get_time(long time_start);
void	print_str(t_philo *philo, char *str);
void	ft_usleep(long long time);

#endif