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
			ft_usleep(global.die_time, &global, philo);
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

		int status;
		pid_t pid;
		int terminated_count = 0;

		// while (terminated_count < global.nr_ph) 
		// {
    	// 	pid = waitpid(-1, &status, 0); // Wait for any child process to terminate
    	// 	if (pid > 0)
        // 		terminated_count++;
		// }
		int i = 0;
		while (i < global.nr_ph)
		{
			sem_wait(death);
			i++;
		}
		for (int i = 0; i < global.nr_ph; i++)
		{
			printf("%d\n", philo[i].pid);
    		kill(philo[i].pid, SIGQUIT);
		}
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

