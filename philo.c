/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:08:29 by yozlu             #+#    #+#             */
/*   Updated: 2025/08/05 18:11:07 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_mutex(t_info *info)
{
    int i;

	info->fork = malloc(sizeof(pthread_mutex_t) * info->philo_count);
	if (!info->fork)
		return 1;
    i = 0;
    while (i < info->philo_count)
    {
        if (pthread_mutex_init(&info->fork[i], NULL))
            return 1;
        i++;
    }
    if (pthread_mutex_init(&info->print_lock, NULL))
        return 1;
    return 0;
}

void parse_args(t_info *info, char **av)
{
    info->philo_count = ft_atoi(av[1]);
    info->time_to_die = ft_atoi(av[2]);
    info->time_to_eat = ft_atoi(av[3]);
    info->time_to_sleep = ft_atoi(av[4]);
    if (av[5])
        info->must_eat_count = ft_atoi(av[5]);
    else
        info->must_eat_count = -1;
}

int main(int ac, char **av)
{
    t_info *info;
    
    info = malloc(sizeof(t_info));
    if (ac != 5 && ac != 6)
        return -1;
    if (check(av) != 0)
        return -1;  
    parse_args(info, av);
    if (init_mutex(info))
        return 1;
    return 0;
}
