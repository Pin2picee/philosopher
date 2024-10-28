/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:47:30 by abelmoha          #+#    #+#             */
/*   Updated: 2024/10/28 18:01:45 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_write_what(char *str, t_philo *philo)
{
	if (check_die(philo))
		return ;
	else
	{
		pthread_mutex_lock(&philo->data->m_write);
		printf("🕐\x1B[1;95m%4ld\x1B[0m🕐->\x1B[33m%d :\x1B[0m %s\n",
			(get_time() - philo->data->start_time), (philo->id + 1), str);
		pthread_mutex_unlock(&philo->data->m_write);
	}
	return ;
}

void	ft_write_die(char *str, t_philo *philo)
{	
	pthread_mutex_lock(&philo->data->m_write);
	if (check_die(philo))
	{
		printf("🕐\x1B[1;92m%ld\x1B[0m🕐\x1B[32m%d :\x1B[0m %s\n",
			(get_time() - philo->data->start_time), (philo->id + 1), str);
		pthread_mutex_unlock(&philo->data->m_write);
	}
	return ;
}

void	*moniteur(void *d)
{
	int		i;
	t_data	*data;

	data = (t_data *)d;
	while (data->flag_die == false && data->flag_finish == false)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_lock(&data->mutex_time_eat);
			if (((int)(get_time() - data->philosopher[i].last_time_eat))
				> data->time_die)
			{
				pthread_mutex_unlock(&data->mutex_time_eat);
				pthread_mutex_lock(&data->mutex_flag_die);
				data->flag_die = true;
				pthread_mutex_unlock(&data->mutex_flag_die);
				ft_write_die(DIE, &data->philosopher[i]);
				return (NULL);
			}
			pthread_mutex_unlock(&data->mutex_time_eat);
			i++;
		}
	}
	return (NULL);
}

int	ft_usleep(long int time)
{
	long int	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}
