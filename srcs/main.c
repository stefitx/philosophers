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

void    join_all(t_philo *philo)
{
    for (int i = 0; i < philo->global->nr_ph; i++)
    {
        pthread_detach(philo[i].thread);
    }
}


int main(int argc, char **argv)
{
    t_global global;
    t_philo *philo;

    if (!wrong_args(argc, argv, &global)) 
    {
        philo = malloc(sizeof(t_philo) * global.nr_ph);
        if (!philo)
            return 0;
        init_philo(&global, philo);
        init_thread(&global, philo);
        global.tm_begin = ft_get_time(0);
        pthread_mutex_unlock(&global.mtx_global);
        pthread_join(global.god_t, NULL);
        join_all(philo);
        free(philo);
    }
    return 0;
}
