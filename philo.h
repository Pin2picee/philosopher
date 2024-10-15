/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:04:21 by abelmoha          #+#    #+#             */
/*   Updated: 2024/10/15 23:20:51 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft/libft.h"
# include <pthread.h>

# define TAKE_FORK_R "Is taking a right fork !"
# define TAKE_FORK_L "Is taking a left fork !"
# define THINK "is thinking"
# define EAT "is eating"
# define SLEEP "is sleeping"

struct s_philo;

typedef struct s_data
{
	struct s_philo 		*philosopher;
	pthread_mutex_t	*mutex;
	pthread_mutex_t m_write;
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_eat;
}			t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	t_data			*data;
	pthread_mutex_t *fork;
	pthread_mutex_t	*fork_left;
}			t_philo;

/*--------------------INIT------------------------*/
int	init_arg(int argc, char **argv, t_data *data);

int	init_data(t_data *data);

void	init_philosopher(t_philo *philo);

/*-------------------ROUTINE-----------------*/
void	ft_write_what(char *str, t_philo *philo, int id);

void	*ft_routine(void *p);

#endif