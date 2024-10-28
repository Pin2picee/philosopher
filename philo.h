/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:04:21 by abelmoha          #+#    #+#             */
/*   Updated: 2024/10/28 18:52:30 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "Libft/libft.h"
# include <pthread.h>
# include <time.h>
# include <sys/time.h>
# include <stdbool.h>

# define TAKE_FORK_R "\x1B[91mIs taking a right fork !\x1B[0m"
# define TAKE_FORK_L "\x1B[94mIs taking a left fork !\x1B[0m"
# define THINK "\x1B[1m---🤔is thinking🤔---\x1B[0m"
# define EAT "\x1B[1m----🍔is eating🍔----\x1B[0m"
# define SLEEP "\x1B[2mᶻ 𝗓 𐰁😴is sleeping😴ᶻ 𝗓 𐰁\x1B[0m"
# define DIE "\x1B[1m                            OH NOOOOOO IM DIEEEEEEE\x1B[0m"

struct	s_philo;

typedef struct s_data
{
	pthread_t		moniteur;
	struct s_philo	*philosopher;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	mutex_time_eat;
	pthread_mutex_t	mutex_flag_die;
	pthread_mutex_t	m_write;
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_eat;
	long int		start_time;
	bool			flag_die;
	bool			flag_finish;
}			t_data;

typedef struct s_philo
{
	pthread_mutex_t	*m_write;
	pthread_t		thread;
	int				id;
	long int		last_time_eat;
	t_data			*data;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*fork_left;
}			t_philo;

/*--------------------INIT------------------------*/
int		init_arg(int argc, char **argv, t_data *data);

int		init_data(t_data **data);

void	init_philosopher(t_philo *philo);

long	get_time(void);

void	ft_philo_rallonge(t_philo *philo);

void	ft_join_thread(t_philo *philo);

/*-------------------ROUTINE-----------------*/
void	ft_write_what(char *str, t_philo *philo);

void	*ft_routine(void *p);

int		ft_usleep(long int time);

int		check_die(t_philo *philo);

/*-----------------MONITEUR-------------------*/
void	*moniteur(void *d);

void	ft_write_die(char *str, t_philo *philo);

#endif