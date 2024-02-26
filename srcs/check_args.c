/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:07:38 by atudor            #+#    #+#             */
/*   Updated: 2024/02/09 21:07:40 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_digit(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i] && i < argc)
	{
		j = 0;
		while (argv[i][j] != 0)
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	wrong_args(int argc, char **argv, t_global *global)
{
	if (argc >= 5 && argc <= 6)
	{
		if (!check_digit(argc, argv))
		{
			pthread_mutex_init(&global->mtx_print, NULL);
			pthread_mutex_init(&global->mtx_global, NULL);
			pthread_mutex_init(&global->mtx_for_death, NULL);
			pthread_mutex_lock(&global->mtx_global);
			global->nr_ph = ft_atoi(argv[1]);
			global->die_time = ft_atoi(argv[2]);
			global->eat_time = ft_atoi(argv[3]);
			global->sleep_time = ft_atoi(argv[4]);
			global->someone_died = 0;
			if (global->nr_ph == 0)
			{
				write(2, "Error!\n", 8);
				return (1);
			}
		//	printf("%d, %d, %d, %d", global->nr_ph, global->die_time , global->eat_time, global->sleep_time);
			if (argc == 6)
				global->nr_must_eat = ft_atoi(argv[5]);
			else if (argc == 5)
				global->nr_must_eat = -1;
			return (0);
		}
	}
	write(2, "Usage: ./philo nr_of_philosophers ", 34);
	write(2, "time_to_die time_to_eat time_to_sleep ", 38);
	write(2, "[nr_of_times_each_philosopher_must_eat]\n", 41);
	return (1);
}

//deal with case of 0 philos