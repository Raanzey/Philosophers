/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:05:59 by yozlu             #+#    #+#             */
/*   Updated: 2025/08/06 17:44:03 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *av)
{
	t_philo *philo = (t_philo*)av;
	
	while (1)
	{
		pthread_mutex_lock(&philo->left_fork);
		pthread_mutex_lock(&philo->right_fork);
		
	}
	
}

void mutex_lock(t_philo *philo)
{
	
}

int start_philo(t_info *info, t_philo *philo)
{
	int i;
	
	i = 0;
	info->start_time = time_ms();
	while (i < info->philo_count)
	{
		philo[i].last_meal = info->start_time;
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
			return 1;
		i++;
	}
	return 0;
}