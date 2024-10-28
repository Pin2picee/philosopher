/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:55:29 by abelmoha          #+#    #+#             */
/*   Updated: 2024/10/28 18:45:08 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all_mutex(t_data *data)
{
	int	i;

	i = data->nb_philo - 1;
	while (i)
	{
		pthread_mutex_destroy(&data->mutex[i]);
		i--;
	}
	pthread_mutex_destroy(&data->mutex_time_eat);
	free(data->mutex);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (!init_data(&data) || !init_arg(argc, argv, data))
	{
		if (data)
			free(data);
		ft_printf("----------------");
		return (1);
	}
	if (data->nb_philo == 1)
	{
		printf("🕐\x1B[1;95m%d\x1B[0m🕐->\x1B[33m%d :\x1B[0m %s\n",
			(data->time_die), 1, "Le philospher se trouvait seul, "
			"il est donc mort de faim");
		return (destroy_all_mutex(data),
			free(data->philosopher), free(data), 1);
	}
	data->flag_finish = false;
	init_philosopher(data->philosopher);
	destroy_all_mutex(data);
	free(data->philosopher);
	if (data)
		free(data);
	return (0);
}
