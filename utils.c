/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:47:30 by abelmoha          #+#    #+#             */
/*   Updated: 2024/10/16 21:44:11 by abelmoha         ###   ########.fr       */
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
	pthread_mutex_lock(philo->m_write);
	printf("🕐\x1B[1;95m%ld\x1B[0m🕐 ----> \x1B[33m%d :\x1B[0m %s\n",(get_time() - philo->data->start_time),  (philo->id + 1), str);
	pthread_mutex_unlock(philo->m_write);
	return ;
}

void	*moniteur(void *d)
{
	int 	i;
	int 	j;
	t_data	*data;
	
	data = (t_data *)d;
	
	j = -1;
	while(1)
	{
		i = 0;
		while (&data->philosopher[i])
		{
			if ((data->philosopher[i].last_time_eat - get_time()) > data->time_die)
			{
				while(&data->mutex[++j])
					pthread_mutex_destroy(&data->mutex[j]);
				break;
			}
			i++;
		}
	}
}
