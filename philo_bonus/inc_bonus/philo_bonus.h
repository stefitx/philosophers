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

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/queue.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[93m"
# define MAGENTA "\x1b[94m"
# define CYAN    "\x1b[96m"
# define WHITE	"\x1b[97m"
# define RESET   "\x1b[0m"

typedef struct s_global
{
	int				nr_ph;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				nr_must_eat;
	long			tm_begin;
	struct s_philo	*philosophers;
	sem_t			*print;
	sem_t			*death;
	sem_t			*forks;
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
void		philo_routine(t_global *global, t_philo *philo, sem_t *forks);
void		init_philo(t_global *global, t_philo *philo);
void		init_process(t_global *global, t_philo *philo, sem_t *forks);
int			case_of_one(t_global *global, t_philo *philo);
void		close_sems(t_global	*global);

//check_args
int			ft_isdigit(char c);
long long	ft_atoi(char *str);
int			check_digit(int argc, char **argv);
void		fill_args(int argc, char **argv, t_global *global);
int			wrong_args(int argc, char **argv, t_global *global);

//utils
long		ft_get_time(long time_start);
void		print_str(t_philo *philo, char *str);
void		ft_usleep(long long time, t_global *global, t_philo *philo);

//routine
int			we_are_full(t_global *global);
void		check_death(t_global *global, t_philo *philo);

#endif