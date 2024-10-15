/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:47:30 by abelmoha          #+#    #+#             */
/*   Updated: 2024/10/15 23:14:36 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_write_what(char *str, t_philo *philo, int id)
{
	pthread_mutex_lock(&philo->data->m_write);
	ft_printf("%d : %s", philo, philo->id + 1, str);
	pthread_mutex_unlock(&philo->data->m_write);
	return ;
}