/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:45:16 by yozlu             #+#    #+#             */
/*   Updated: 2025/08/12 16:16:29 by yozlu            ###   ########.fr       */
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
	int philo_count;            // Filozof (ve çatal) sayısı
	int time_to_die;            // Bir filozofun yemeden önce en fazla yaşayabileceği süre (ms)
	int time_to_eat;            // Yemek yeme süresi (ms)
	int time_to_sleep;          // Uyuma süresi (ms)
	int must_eat_count;         // Her filozofun kaç kez yemesi gerektiği (opsiyonel),-1 ise zorunlu değil
	int someone_died;           // Herhangi bir filozof öldüyse 1 yapılır → tüm simülasyon durur
	long start_time;            // Simülasyonun başladığı zaman (ms cinsinden)
	pthread_mutex_t *fork;      // Her çatal için bir mutex (çatal kilidi)
	pthread_mutex_t print_lock; // Ekrana yazdırmayı sıraya koymak için kullanılan mutex
	pthread_mutex_t	death_lock;
}					t_info;

typedef struct s_philo
{
	int id;                      // Filozofun numarası (1'den başlar)
	int eat_count;               // Şu ana kadar kaç kez yemek yedi
	long last_meal;              // En son yemek yediği zaman (ms cinsinden)
	pthread_t thread;            // Bu filozofun thread’i (pthread_create ile çalıştırılır)
	pthread_mutex_t *left_fork;  // Solundaki çatalın mutex’i
	pthread_mutex_t *right_fork; // Sağındaki çatalın mutex’i
	pthread_mutex_t	meal_lock;
	t_info *info; 				 // Genel simülasyon bilgilerine erişim için pointer (t_info)
}					t_philo;

int					check(char **str);
int					time_ms(void);
int					ft_atoi(const char *str);
int					start_thread(t_info *info, t_philo *philo);
int					get_someone_died(t_info *info);
int					 check_death(t_philo *philo, t_info *info, int i);
void				set_someone_died(t_info *info, int value);
void				print_state(t_philo *philo, char *msg);
void				ft_usleep(long ms);
void				destroy_all(t_info *info, t_philo *philo);
void				take_forks(t_philo *philo);
void				eat_and_sleep(t_philo *philo);

#endif