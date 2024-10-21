/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:47:30 by abelmoha          #+#    #+#             */
/*   Updated: 2024/10/17 20:04:20 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//get_time renvoie gettimeofday en miliseconde 
long int get_time(void)
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_write_what(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_flag_die);
	if (philo->data->flag_die == false)
	{
		pthread_mutex_unlock(&philo->data->mutex_flag_die);
		pthread_mutex_lock(&philo->data->m_write);
		printf("🕐\x1B[1;95m%ld\x1B[0m🕐->\x1B[33m%d :\x1B[0m %s\n",(get_time() - philo->data->start_time),  (philo->id + 1), str);
		pthread_mutex_unlock(&philo->data->m_write);
	}
	else
		pthread_mutex_unlock(&philo->data->mutex_flag_die);
	return ;
}



void	ft_write_die(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_flag_die);
	philo->data->flag_die = true;
	pthread_mutex_unlock(&philo->data->mutex_flag_die);
	pthread_mutex_lock(&philo->data->m_write);
	printf("🕐\x1B[1;92m%ld\x1B[0m🕐\x1B[32m%d :\x1B[0m %s\n",(get_time() - philo->data->start_time),  (philo->id + 1), str);
	pthread_mutex_unlock(&philo->data->m_write);
	return ;
}

void	*moniteur(void *d)
{
	int 	i;
	t_data	*data;
	int		j = 0;
	
	data = (t_data *)d;
	
	while(1)
	{
		i = 0;
		while (i < data->nb_philo )
		{
			pthread_mutex_lock(&data->mutex_time_eat);
			if (((int)(get_time() - data->philosopher[i].last_time_eat)) > data->time_die)
			{
				pthread_mutex_unlock(&data->mutex_time_eat);
				ft_write_die(DIE, &data->philosopher[i]);
				return (NULL);
			}
			pthread_mutex_unlock(&data->mutex_time_eat);
			i++;
		}
		ft_usleep(100);
	}
}
void	ft_usleep(long nb)
{
	long start;
	long end;

	start = get_time();
	end = start + nb;
	while (get_time() < end)
	{
		usleep(100);
	}
	return ;
}