/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:50:11 by abelmoha          #+#    #+#             */
/*   Updated: 2024/10/15 23:24:45 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo, char parameter)
{
	if (parameter == 'r')
	{
		pthread_mutex_lock(philo->fork);
		ft_printf(TAKE_FORK_R);
	}
	if (parameter == 'L')
	{
		pthread_mutex_lock(philo->fork_left);
		ft_printf(TAKE_FORK_L);
	}
}

void	eat_philo(t_philo *philo)
{
	ft_write_what(THINK, philo, philo->id);
	take_fork(philo, 'r');
	take_fork(philo, 'l');
	ft_write_what(EAT, philo, philo->id);
	usleep(philo->data->time_eat);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork);
}

void	sleep_philo(t_philo *philo)
{
	ft_write_what(SLEEP, philo, philo->id);
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
}
