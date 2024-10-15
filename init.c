/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:07:49 by abelmoha          #+#    #+#             */
/*   Updated: 2024/10/15 21:19:46 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data)
{
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	ft_memset(data, 0, sizeof(t_data));
	data->philosopher = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philosopher)
	{
		free(data);
		return (0);
	}
	return (1);
}

int	init_arg(int argc, char **argv, t_data *data)
{
	int	i;

	i = 1;
	data->nb_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nb_eat = ft_atoi(argv[5]);
	data->mutex = malloc(sizeof(pthread_t) * data->nb_philo);
	if (data->mutex == NULL)
		return (0);
	while (i <= data->nb_philo)//init des mutex------
	{
		pthread_mutex_init(&data->mutex[i], NULL);
		i++;
	}
	return (1);
}

//./a.out	5 422 355 50 [nb_eat]
void	init_philopher(t_philo *philo)
{
	
}