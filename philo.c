/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:10:07 by yozlu             #+#    #+#             */
/*   Updated: 2025/05/03 16:12:04 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
    if (ac != 5 && ac != 6)
        return -1;
    if (check(av) != 0)
        return -1;
        
    return 0;
}
