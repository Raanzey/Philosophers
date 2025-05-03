/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:36:50 by yozlu             #+#    #+#             */
/*   Updated: 2025/05/02 18:45:32 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_info
{
	int philo_count;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int must_eat_count;
	int someone_died;
	int start_time;
	pthread_mutex_t *fork;
	pthread_mutex_t print_lock;
}t_info;

typedef struct s_philo
{
	int id;
	int eat_count;
	long last_meal;
	pthread_t thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	t_info *info;
}t_philo;


int check(char **str);

#endif