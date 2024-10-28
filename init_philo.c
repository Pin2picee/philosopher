/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:24:15 by abelmoha          #+#    #+#             */
/*   Updated: 2024/10/28 17:57:37 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_join_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	pthread_join(philo->data->moniteur, NULL);
	return ;
}

void	init_philosopher(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		philo[i].m_write = &philo->data->m_write;
		philo[i].id = i;
		philo[i].fork = &philo->data->mutex[i];
		if ((i + 1) == philo->data->nb_philo)
			philo[i].fork_left = &philo->data->mutex[0];
		else
			philo[i].fork_left = &philo->data->mutex[i + 1];
		i++;
	}
	ft_philo_rallonge(philo);
}

void	ft_philo_rallonge(t_philo *philo)
{
	int	i;

	i = 0;
	philo->data->start_time = get_time();
	pthread_mutex_init(&philo->data->mutex_time_eat, NULL);
	pthread_mutex_init(&philo->data->mutex_flag_die, NULL);
	philo->data->flag_die = false;
	while (i < philo->data->nb_philo)
	{
		pthread_create(&philo[i].thread, NULL, ft_routine, &philo[i]);
		pthread_mutex_lock(&philo[i].data->mutex_time_eat);
		philo[i].last_time_eat = get_time();
		pthread_mutex_unlock(&philo[i].data->mutex_time_eat);
		i++;
	}
	pthread_create(&philo->data->moniteur, NULL, moniteur, philo->data);
	ft_join_thread(philo);
}

int	check_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_flag_die);
	if (philo->data->flag_die == true)
	{
		pthread_mutex_unlock(&philo->data->mutex_flag_die);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex_flag_die);
	return (0);
}
