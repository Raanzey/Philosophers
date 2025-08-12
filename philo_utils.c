/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:05:59 by yozlu             #+#    #+#             */
/*   Updated: 2025/08/12 16:17:49 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_full(t_philo *philo, t_info *info, int *full_philos)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < info->philo_count)
	{
		pthread_mutex_lock(&philo[i].meal_lock);
		if (info->must_eat_count != -1
			&& philo[i].eat_count >= info->must_eat_count)
			count++;
		pthread_mutex_unlock(&philo[i].meal_lock);
		i++;
	}
	*full_philos = count;
	if (info->must_eat_count != -1 && *full_philos == info->philo_count)
	{
		set_someone_died(info, 1);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_philo	*philo;
	t_info	*info;
	int		i;
	int		full_philos;

	philo = (t_philo *)arg;
	info = philo[0].info;
	while (!info->someone_died)
	{
		i = 0;
		if (check_full(philo, info, &full_philos))
			return (NULL);
		while (i < info->philo_count)
		{
			if (check_death(philo, info, i))
				return (NULL);
			i++;
		}
		ft_usleep(1);
	}
	return (NULL);
}

static void	philo_loop(t_philo *philo)
{
	int	ate_enough;

	while (!get_someone_died(philo->info))
	{
		pthread_mutex_lock(&philo->meal_lock);
		ate_enough = (philo->info->must_eat_count != -1
				&& philo->eat_count >= philo->info->must_eat_count);
		pthread_mutex_unlock(&philo->meal_lock);
		if (ate_enough)
			break ;
		print_state(philo, "is thinking");
		take_forks(philo);
		eat_and_sleep(philo);
	}
}

void	*routine(void *av)
{
	t_philo	*philo;

	philo = (t_philo *)av;
	if (philo->info->philo_count == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_unlock(philo->left_fork);
		ft_usleep(philo->info->time_to_die);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(1);
	philo_loop(philo);
	return (NULL);
}

int	start_thread(t_info *info, t_philo *philo)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	info->start_time = time_ms();
	while (i < info->philo_count)
	{
		philo[i].last_meal = info->start_time;
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor, philo) != 0)
		return (1);
	if (pthread_join(monitor_thread, NULL) != 0)
		return (1);
	i = 0;
	while (i < info->philo_count)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	destroy_all(info, philo);
	return (0);
}
