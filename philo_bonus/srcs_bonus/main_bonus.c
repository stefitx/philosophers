/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:13:29 by atudor            #+#    #+#             */
/*   Updated: 2024/02/28 20:13:31 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/philo_bonus.h"

void	close_sems(t_global	*global)
{
	sem_close(global->forks);
	sem_unlink("forks");
	sem_close(global->death);
	sem_unlink("death");
	sem_close(global->print);
	sem_unlink("print");
	free(global->philosophers);
}

void	terminate(t_global *global)
{
	int		status;
	pid_t	pid;
	int		terminated_count;
	int		i;

	terminated_count = 0;
	i = 0;
	while (i < global->nr_ph)
	{
		sem_wait(global->death);
		i++;
	}
	i = 0;
	while (i < global->nr_ph)
	{
		kill(global->philosophers[i].pid, SIGQUIT);
		i++;
	}
	close_sems(global);
}

void	init_global(t_global *global, sem_t *forks, sem_t *death, sem_t *print)
{
	global->death = death;
	global->forks = forks;
	global->print = print;
	global->tm_begin = ft_get_time(0);
}

int	main(int argc, char **argv)
{
	t_global	global;
	t_philo		*philo;
	sem_t		*forks;
	sem_t		*death;
	sem_t		*print;

	if (!wrong_args(argc, argv, &global))
	{
		philo = malloc(sizeof(t_philo) * global.nr_ph);
		if (!philo)
			return (0);
		forks = sem_open("forks", O_CREAT, 0644, global.nr_ph);
		death = sem_open("death", O_CREAT, 0644, 0);
		print = sem_open("print", O_CREAT, 0644, 1);
		if (case_of_one(&global, philo) == 1)
			return (0);
		init_philo(&global, philo);
		init_global(&global, forks, death, print);
		init_process(&global, philo, forks);
		terminate(&global);
	}
	return (0);
}
