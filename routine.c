/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:50:11 by abelmoha          #+#    #+#             */
/*   Updated: 2024/10/17 19:40:24 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo)
{
	if ((philo->id + 1) % 2 != 0) // impair
	{
		pthread_mutex_lock(philo->fork);
		ft_write_what(TAKE_FORK_R, philo);
		pthread_mutex_lock(philo->fork_left);
		ft_write_what(TAKE_FORK_L, philo);
	}
	else
	{
		pthread_mutex_lock(philo->fork_left); // pair
		ft_write_what(TAKE_FORK_L, philo);
		pthread_mutex_lock(philo->fork);
		ft_write_what(TAKE_FORK_R, philo);
	}
}
void	ft_last_time_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_time_eat);
	philo->last_time_eat = get_time();
	pthread_mutex_unlock(&philo->data->mutex_time_eat);
}

void	eat_philo(t_philo *philo)
{
	take_fork(philo);
	ft_write_what(EAT, philo);
	ft_last_time_eat(philo);
	ft_usleep(philo->data->time_eat);
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(philo->fork_left);
}


void	sleep_philo(t_philo *philo)
{
	ft_write_what(SLEEP, philo);
	ft_usleep(philo->data->time_sleep);
	ft_write_what(THINK, philo);
}

void	*ft_routine(void *p)
{
	int	i;
	t_philo *philo;
	
	philo = (t_philo *)p;
	// chaque philo rentre dans sa fonction routine alterne entre manger et dormir
	i = 0;
	pthread_mutex_lock(&philo->data->mutex_time_eat);
	philo->last_time_eat = get_time();
	pthread_mutex_unlock(&philo->data->mutex_time_eat);
	if ((philo->id % 2) == 0)
		ft_usleep(200);
	while (i != philo->data->nb_eat)
	{
		pthread_mutex_lock(&philo->data->mutex_flag_die);
		if (philo->data->flag_die == true)
		{
			pthread_mutex_unlock(&philo->data->mutex_flag_die);
			break;
		}
		pthread_mutex_unlock(&philo->data->mutex_flag_die);
		eat_philo(philo);
		sleep_philo(philo);
		i++;
	}
	ft_write_what("\x1b[1mMIAM MIAM, trop bonnnn\x1b[0m", philo);
	return (NULL);
}
