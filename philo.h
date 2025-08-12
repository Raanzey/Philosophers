/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:45:16 by yozlu             #+#    #+#             */
/*   Updated: 2025/08/12 17:09:19 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_info
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				someone_died;
	long			start_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
}					t_info;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock;
	t_info			*info;
}					t_philo;

int					check(char **str);
int					time_ms(void);
int					ft_atoi(const char *str);
int					start_thread(t_info *info, t_philo *philo);
int					get_someone_died(t_info *info);
int					check_death(t_philo *philo, t_info *info, int i);
void				set_someone_died(t_info *info, int value);
void				print_state(t_philo *philo, char *msg);
void				ft_usleep(long ms);
void				destroy_all(t_info *info, t_philo *philo);
void				take_forks(t_philo *philo);
void				eat_and_sleep(t_philo *philo);

#endif