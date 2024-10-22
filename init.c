/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:07:49 by abelmoha          #+#    #+#             */
/*   Updated: 2024/10/17 18:49:17 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data **data)
{
	*data = malloc(sizeof(t_data));
	if (!(*data))
		return (0);
	ft_memset((*data), 0, sizeof(t_data));
	return (1);
}

int	init_arg_2(t_data *data, char **argv, int argc)
{
	if (argc != 5 && argc != 6)
		return (0);
	data->nb_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	return (1);
}

int	init_arg(int argc, char **argv, t_data *data)
{
	int	i;

	i = 0;
	if (!init_arg_2(data, argv, argc))
		return (ft_printf("probleme avec le nombre d'un argument !"), 0);
	if (data->nb_philo > 200 || data->time_die < 60 || data->time_eat < 60 || data->time_sleep < 60)
			return (ft_printf("probleme avec le temps d'un argument !"), 0);
	if (argc == 6)
		data->nb_eat = ft_atoi(argv[5]);
	else
		data->nb_eat = -1;
	data->mutex = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (data->mutex == NULL)
		return (0);
	data->philosopher = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philosopher)
		return (free(data->mutex), 0);
	while (i < data->nb_philo)//init des mutex------
	{
		data->philosopher[i].data = data;
		pthread_mutex_init(&data->mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->m_write, NULL);
	return (1);
}

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
		if ((i + 1) == philo->data->nb_philo )
			philo[i].fork_left = &philo->data->mutex[0];
		else
			philo[i].fork_left = &philo->data->mutex[i + 1];
		i++;
	}
	i = 0;
	philo->data->start_time = get_time();
	pthread_mutex_init(&philo->data->mutex_time_eat, NULL); 
	pthread_mutex_init(&philo->data->mutex_flag_die, NULL); 
	philo->data->flag_die = false;
	while (i < philo->data->nb_philo)
	{
		pthread_create(&philo[i].thread, NULL, ft_routine, &philo[i]);
		i++;
	}
	pthread_create(&philo->data->moniteur, NULL, moniteur, philo->data);
	ft_join_thread(philo);
}
