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

int    case_of_one(t_global *global, t_philo *philo)
{
    if (global->nr_ph == 1)
    {
        pthread_mutex_init(&philo[0].right_fork, NULL);
        philo[0].id = 1;
        global->philosophers = philo;
        philo[0].global = global;
        global->tm_begin = ft_get_time(0);
        pthread_create(&philo[0].thread, NULL, &philo_one, &philo[0]);
        pthread_join(philo[0].thread, NULL);
        free(philo);
        return 1;
    }
    return 0;
}

void    *philo_one(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    pthread_mutex_lock(&philo->right_fork);
    print_str(philo, "has taken right fork");
    ft_usleep(philo->global->die_time);
    print_str(philo, "has died");
    return NULL;
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
        if (case_of_one(&global, philo) == 1)
            return 0;
        init_philo(&global, philo);
        init_thread(&global, philo);
        global.tm_begin = ft_get_time(0);
        pthread_mutex_unlock(&global.mtx_global);
        god(&global);
        join_all(philo);
        free(philo);
    }
    return 0;
}