/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:55:29 by abelmoha          #+#    #+#             */
/*   Updated: 2024/10/12 18:04:33 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data *data;
	
	
	if (argc != 5 || argc != 6)
		return (1);
	if (!init_data(data) || !init_arg(argc, argv, data))
	{
		if (data)
			free(data);
		return (1);
	}
	init_philosopher()
	return (0);
}
