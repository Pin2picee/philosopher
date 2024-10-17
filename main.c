/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:55:29 by abelmoha          #+#    #+#             */
/*   Updated: 2024/10/16 13:05:04 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data *data;
	
	
	if (!init_data(&data) || !init_arg(argc, argv, data))
	{
		if (data)
			free(data);
		ft_printf("----------------");
		return (1);
	}
	init_philosopher(data->philosopher);
	return (0);
}
