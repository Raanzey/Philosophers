/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:05:59 by yozlu             #+#    #+#             */
/*   Updated: 2025/08/08 05:45:03 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_state(t_philo *philo, char *msg)
{
	long timestamp;

	pthread_mutex_lock(&philo->info->print_lock);
	timestamp = time_ms() - philo->info->start_time;
	if (!philo->info->someone_died)
		printf("%ld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->info->print_lock);
}

void destroy_all(t_info *info)
{
    int i = 0;

    // Tüm çatal mutex'lerini yok et
    while (i < info->philo_count)
    {
        pthread_mutex_destroy(&info->fork[i]);
        i++;
    }

    // Print lock'u yok et
    pthread_mutex_destroy(&info->print_lock);
}

void *monitor(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_info *info = philo[0].info;
	int i;
	int full_philos;

	while (!info->someone_died)
	{
		i = 0;
		full_philos = 0;
		while (i < info->philo_count)
		{
			long now = time_ms();
			if ((now - philo[i].last_meal) > info->time_to_die)
			{
				print_state(&philo[i], "died");
				info->someone_died = 1;
				return NULL;
			}
			if (info->must_eat_count != -1 && philo[i].eat_count >= info->must_eat_count)
				full_philos++;
			i++;
		}
		if (info->must_eat_count != -1 && full_philos == info->philo_count)
		{
			info->someone_died = 1;
			return NULL;
		}
		usleep(1000); // Ölüm tespitini 10ms altında garantilemek için yeterli
	}
	return NULL;
}

void *routine(void *av)
{
	t_philo *philo = (t_philo*)av;
	
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!philo->info->someone_died) // Simülasyon bir filozofun ölmesiyle biter; ölmediği sürece döngü devam eder
	{
		// THINKING
		print_state(philo, "is thinking"); // Filozofun "düşünüyor" durumu ekrana yazdırılır

		// FORK AL
		pthread_mutex_lock(philo->left_fork);           // Solundaki çatala erişim için kilit alır (mutex lock)
		print_state(philo, "has taken a fork");         // Log basılır: "X has taken a fork"

		pthread_mutex_lock(philo->right_fork);          // Sağındaki çatala erişim için kilit alır
		print_state(philo, "has taken a fork");         // İkinci çatal için log basılır

		// EAT
		print_state(philo, "is eating");                // "X is eating" logu yazılır
		philo->last_meal = time_ms();                   // En son yemek yediği zaman güncellenir (ölüm kontrolü için)
		philo->eat_count++;                             // Kaç kez yediğini sayar (opsiyonel argüman varsa kontrol için)
		usleep(philo->info->time_to_eat * 1000);        // Yemek süresi kadar bekler (milisaniyeyi mikrosaniyeye çevir)

		// FORK BIRAK
		pthread_mutex_unlock(philo->left_fork);         // Sol çatalı bırakır (mutex unlock)
		pthread_mutex_unlock(philo->right_fork);        // Sağ çatalı bırakır

		// SLEEP
		print_state(philo, "is sleeping");              // "X is sleeping" logu yazılır
		usleep(philo->info->time_to_sleep * 1000);      // Uyuma süresi kadar bekler
	}
	return (NULL); // Thread başarıyla sonlanır
}


int start_thread(t_info *info, t_philo *philo)
{
	int i;
	pthread_t monitor_thread;
	
	i = 0;
	info->start_time = time_ms();
	while (i < info->philo_count)
	{
		philo[i].last_meal = info->start_time;
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
			return 1;
		i++;
	}
		// Monitor thread'ini başlat
	if (pthread_create(&monitor_thread, NULL, monitor, philo) != 0)
		return (1);

	// Monitor thread'ini bekle (diğerlerini durdurmak için)
	if (pthread_join(monitor_thread, NULL) != 0)
		return (1);

	// Filozof thread'lerini bekle
	i = 0;
	while (i < info->philo_count)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	destroy_all(info);
	return (0);
}
