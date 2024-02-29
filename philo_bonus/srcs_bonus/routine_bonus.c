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

	last_time_eaten = philo->last_time_eaten;
	current_time = ft_get_time(global->tm_begin);
	if (current_time - last_time_eaten > global->die_time)
	{
		sem_wait(global->print);
		printf("[%lu] %d has died\n", current_time, philo->id);

		for (int i = 0; i < global->nr_ph * 2; i++)
			sem_post(global->death);
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
			printf("[%lu] %d is full\n", tm, philo->id);
			sem_post(global->print);
			sem_post(global->death);
			exit(0);
		}
	}
	return (0);
}

void	philo_routine(t_global *global, t_philo *philo, sem_t *forks)
{
	int i = 0;
	while (1)
	{
		check_death(global, philo);
		sem_wait(forks);
		print_str(philo, "has taken right fork");
		check_death(global, philo);
		sem_wait(forks);
		check_death(global, philo);
		print_str(philo, "has taken left fork");
		check_death(global, philo);
		print_str(philo, "is eating");
		philo->times_eaten++;
		philo->last_time_eaten = ft_get_time(philo->global->tm_begin);
		ft_usleep(philo->global->eat_time, global, philo);
		sem_post(forks);
		sem_post(forks);
		if (check_meals(global, philo) == 1)
			break ;
		check_death(global, philo);
		print_str(philo, "is sleeping");
		ft_usleep(philo->global->sleep_time, global, philo);
		check_death(global, philo);
		print_str(philo, "is thinking");
		i++;
	}
	return ;
}

// ❯ ./philo_bonus 5 1 20 200
// [0] 1 has taken right fork
// [0] 1 has taken left fork
// [0] 1 is eating
// [0] 2 has taken right fork
// [0] 2 has taken left fork
// [0] 2 is eating
// [0] 3 has taken right fork
// [21] 1 has died

//fix this!!