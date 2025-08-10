/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:28:00 by yozlu             #+#    #+#             */
/*   Updated: 2025/08/10 19:52:44 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo, t_info *info, int i)
{
	long	now;
	long	last_meal;

	now = time_ms();
	pthread_mutex_lock(&philo[i].meal_lock);
	last_meal = philo[i].last_meal;
	pthread_mutex_unlock(&philo[i].meal_lock);
	if ((now - last_meal) > info->time_to_die)
	{
		print_state(&philo[i], "died");
		set_someone_died(info, 1);
		return (1);
	}
	return (0);
}

void	set_someone_died(t_info *info, int value)
{
	pthread_mutex_lock(&info->death_lock);
	info->someone_died = value;
	pthread_mutex_unlock(&info->death_lock);
}

int	get_someone_died(t_info *info)
{
	int	val;

	pthread_mutex_lock(&info->death_lock);
	val = info->someone_died;
	pthread_mutex_unlock(&info->death_lock);
	return (val);
}

void	print_state(t_philo *philo, char *msg)
{
	long	time;

	pthread_mutex_lock(&philo->info->print_lock);
	time = time_ms() - philo->info->start_time;
	if (!get_someone_died(philo->info))
		printf("%ld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->info->print_lock);
}

void	destroy_all(t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < info->philo_count)
	{
		pthread_mutex_destroy(&info->fork[i]);
		pthread_mutex_destroy(&philo[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&info->print_lock);
}
