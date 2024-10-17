/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:50:11 by abelmoha          #+#    #+#             */
/*   Updated: 2024/10/16 21:49:43 by abelmoha         ###   ########.fr       */
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

void	eat_philo(t_philo *philo)
{	
	take_fork(philo);
	ft_write_what(EAT, philo);
	philo[philo->id].last_time_eat = get_time();
	usleep(philo->data->time_eat * 1000);
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(philo->fork_left);
}

void	sleep_philo(t_philo *philo)
{
	ft_write_what(SLEEP, philo);
	usleep(philo->data->time_sleep * 1000);
	ft_write_what(THINK, philo);
}

void	*ft_routine(void *p)
{
	int	i;
	t_philo *philo;
	
	philo = (t_philo *)p;
	// chaque philo rentre dans sa fonction routine alterne entre manger et dormir
	i = 0;
	while (i != philo->data->nb_eat)
	{
		eat_philo(philo);
		sleep_philo(philo);
		i++;
	}
	ft_write_what("fini", philo);
}
