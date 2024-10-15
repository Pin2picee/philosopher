/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:04:21 by abelmoha          #+#    #+#             */
/*   Updated: 2024/10/15 21:00:09 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft/libft.h"
# include <pthread.h>

typedef struct s_data
{
	t_philo 		*philosopher;
	pthread_mutex_t	*mutex;
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_eat;
}			t_data;

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	t_data	*data;
}			t_philo;


int	init_arg(int argc, char **argv, t_data *data);

int	init_data(t_data *data);

#endif