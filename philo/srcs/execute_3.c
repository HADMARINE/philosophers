/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:54:35 by lhojoon           #+#    #+#             */
/*   Updated: 2024/06/04 19:15:47 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_action(void *arg)
{
	unsigned long	last_eat;

	wait_start((t_philo *)arg);
	last_eat = get_timestamp();
	while (true)
	{
		if (check_died((t_philo *)arg, last_eat) == false)
			break ;
		if (((t_philo *)arg)->eat_count
			== ((t_philo *)arg)->data->num_of_must_eat)
			break ;
		if (!ph_eat((t_philo *)arg, &last_eat))
		{
			pthread_mutex_lock(&((t_philo *)arg)->data->print_mutex);
			printf("%lu %d died\n",
				get_time_diff(((t_philo *)arg)->data), ((t_philo *)arg)->id);
			pthread_mutex_unlock(&((t_philo *)arg)->data->print_mutex);
			break ;
		}
		((t_philo *)arg)->eat_count++;
		ph_sleep((t_philo *)arg, &last_eat);
	}
	return (NULL);
}

bool	check_died_noprint(t_philo *arg, unsigned long last_eat)
{
	unsigned long	current_time;
	unsigned int	ttd;
	bool			is_died;

	current_time = get_timestamp();
	if (check_same_args(arg) == false)
		return (false);
	pthread_mutex_lock(&arg->data->mutex);
	ttd = arg->data->time_to_die;
	is_died = arg->data->is_died;
	pthread_mutex_unlock(&arg->data->mutex);
	if (current_time - last_eat > (unsigned long)(ttd) || is_died == true)
	{
		pthread_mutex_lock(&arg->data->mutex);
		arg->data->is_died = true;
		pthread_mutex_unlock(&arg->data->mutex);
		return (false);
	}
	return (true);
}

unsigned long	get_time_diff(t_data *dat)
{
	return (get_timestamp() - dat->time_started);
}
