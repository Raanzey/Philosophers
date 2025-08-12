/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:08:29 by yozlu             #+#    #+#             */
/*   Updated: 2025/08/12 14:54:28 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_info *info)
{
	int	i;

	info->fork = malloc(sizeof(pthread_mutex_t) * info->philo_count);
	if (!info->fork)
		return (1);
	i = 0;
	while (i < info->philo_count)
	{
		if (pthread_mutex_init(&info->fork[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&info->print_lock, NULL))
		return (1);	
	if (pthread_mutex_init(&info->death_lock, NULL))
		return (1);
	return (0);
}

void	init_philo(t_philo *philo, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_count)
	{
		philo[i].id = i + 1;
		philo[i].eat_count = 0;
		philo[i].info = info;
		philo[i].left_fork = &info->fork[i];
		philo[i].right_fork = &info->fork[(i + 1) % info->philo_count];
		philo[i].last_meal = 0;
		pthread_mutex_init(&philo[i++].meal_lock, NULL);
	}
}

void	parse_args(t_info *info, char **av)
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

int	main(int ac, char **av)
{
	t_info	*info;
	t_philo	*philo;

	info = malloc(sizeof(t_info));
	if (ac != 5 && ac != 6)
		return (-1);
	if (check(av) != 0)
		return (-1);
	parse_args(info, av);
	if (init_mutex(info))
		return (1);
	philo = malloc(sizeof(t_philo) * info->philo_count);
	init_philo(philo, info);
	start_thread(info, philo);
	return (0);
}
