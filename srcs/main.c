/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:40:14 by atudor            #+#    #+#             */
/*   Updated: 2024/02/07 17:44:57 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_global	global;
	t_philo		*philo;
	//pthread_t god_thread;

	if (!wrong_args(argc, argv, &global))
	{
		philo = malloc(sizeof(t_philo) * global.nr_ph);
		if (!philo)
			return 0;
		init_philo(&global, philo);
		init_thread(&global, philo);
		global.tm_begin = ft_get_time(0);
		pthread_mutex_unlock(&global.mtx_global);
		god(philo, &global);
		// if(god(philo, &global) == 1)
		// {
		// 	pthread_mutex_unlock(&global.mtx_print);
		// 	return 1;
		// }
	}
	 for (int i = 0; i < global.nr_ph; i++) {
         pthread_join(philo[i].thread, NULL);
     }
		return 0;
}