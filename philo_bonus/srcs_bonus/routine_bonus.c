/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:19:31 by atudor            #+#    #+#             */
/*   Updated: 2024/02/28 20:19:33 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/philo_bonus.h"

void	check_death(t_global *global, t_philo *philo)
{
	long	last_time_eaten;
	long	current_time;
	int		i;

	last_time_eaten = philo->last_time_eaten;
	current_time = ft_get_time(global->tm_begin);
	if (current_time - last_time_eaten > global->die_time)
	{
		sem_wait(global->print);
		printf(RED "[%lu] %d died\n" RESET, current_time, philo->id);
		i = 0;
		while (i < global->nr_ph * 2)
		{
			sem_post(global->death);
			i++;
		}
		exit(0);
	}
}

int	check_meals(t_global *global, t_philo *philo)
{
	long	tm;

	if (global->nr_must_eat != -1)
	{
		if (philo->times_eaten == global->nr_must_eat)
		{
			philo->i_am_full = 1;
			tm = ft_get_time(philo->global->tm_begin);
			sem_wait(global->print);
			printf(MAGENTA "[%lu]" GREEN " %d is full\n" RESET, tm, philo->id);
			sem_post(global->print);
			sem_post(global->death);
			return (1);
		}
	}
	return (0);
}

void	routine_part_one(t_global *global, t_philo *philo, sem_t *forks)
{
	check_death(global, philo);
	sem_wait(forks);
	print_str(philo, "has taken a fork");
	check_death(global, philo);
	sem_wait(forks);
	check_death(global, philo);
	print_str(philo, "has taken a fork");
	check_death(global, philo);
	print_str(philo, "is eating");
}

void	philo_routine(t_global *global, t_philo *philo, sem_t *forks)
{
	int	i;

	i = 0;
	while (1)
	{
		routine_part_one(global, philo, forks);
		philo->times_eaten++;
		philo->last_time_eaten = ft_get_time(philo->global->tm_begin);
		ft_usleep(philo->global->eat_time, global, philo);
		sem_post(forks);
		sem_post(forks);
		if (check_meals(global, philo) == 1)
			exit(0);
		check_death(global, philo);
		print_str(philo, "is sleeping");
		ft_usleep(philo->global->sleep_time, global, philo);
		check_death(global, philo);
		print_str(philo, "is thinking");
		i++;
	}
	return ;
}
