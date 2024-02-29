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
		{
			sem_close(forks);
			sem_unlink("forks");
			sem_close(death);
			sem_unlink("death");
			sem_close(print);
			sem_unlink("print");
			free(philo);
			return (0);
		}
		init_philo(&global, philo);

		global.death = death;
		global.forks = forks;
		global.print = print;
		global.tm_begin = ft_get_time(0);
		init_process(&global, philo, forks);
		if (global.nr_must_eat > 0)
		{
			int i = 0;
			while (i < global.nr_ph)
				{
					sem_wait(death);
					i++;
				}
		}
		else
			sem_wait(death);
		for (int i = 0; i < global.nr_ph; i++)
    		kill(philo[i].pid, SIGQUIT);
		sem_close(forks);
		sem_unlink("forks");
		sem_close(death);
		sem_unlink("death");
		sem_close(print);
		sem_unlink("print");
		free(philo);
	}
	return (0);
}

