/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:12:39 by lhojoon           #+#    #+#             */
/*   Updated: 2024/05/05 18:43:36 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_died(t_philo *arg, unsigned long last_eat)
{
	unsigned long	current_time;
	unsigned int	ttd;
	bool			is_died;

	current_time = get_timestamp();
	if (check_same_args(arg) == false)
		return (pthread_mutex_lock(&arg->data->print_mutex),
			printf("%lu %d died\n", get_timestamp(), arg->id),
			pthread_mutex_unlock(&arg->data->print_mutex),
			false);
	pthread_mutex_lock(&arg->data->mutex);
	ttd = arg->data->time_to_die;
	is_died = arg->data->is_died;
	pthread_mutex_unlock(&arg->data->mutex);
	if (current_time - last_eat > (unsigned long)(ttd) || is_died == true)
	{
		pthread_mutex_lock(&arg->data->mutex);
		arg->data->is_died = true;
		pthread_mutex_unlock(&arg->data->mutex);
		pthread_mutex_lock(&arg->data->print_mutex);
		printf("%lu %d died\n", get_timestamp(), arg->id);
		pthread_mutex_unlock(&arg->data->print_mutex);
		return (false);
	}
	return (true);
}

static void
	wait_all_philo_while_do(bool *is_entered, bool *initialized, t_philo **tp)
{
	pthread_mutex_unlock(&(*tp)->data->mutex);
	*is_entered = true;
	pthread_mutex_lock(&(*tp)->data->mutex);
	*initialized = (*tp)->initialized;
	pthread_mutex_unlock(&(*tp)->data->mutex);
	*tp = (*tp)->right_philo;
	pthread_mutex_lock(&(*tp)->data->mutex);
}

void	wait_all_philo(t_philo *philo)
{
	t_philo	*tp;
	bool	is_entered;
	bool	initialized;

	tp = philo;
	is_entered = false;
	while (true)
	{
		pthread_mutex_lock(&tp->data->mutex);
		while (tp->id != 1 || !is_entered)
			wait_all_philo_while_do(&is_entered, &initialized, &tp);
		pthread_mutex_unlock(&tp->data->mutex);
		ft_usleep(10, philo->data);
		if (initialized == true)
		{
			pthread_mutex_lock(&philo->data->mutex);
			philo->data->is_started = true;
			pthread_mutex_unlock(&philo->data->mutex);
			break ;
		}
		is_entered = false;
	}
}

void	join_all_philo(t_philo *philo)
{
	t_philo	*tp;
	bool	is_entered;

	tp = philo;
	is_entered = false;
	while (tp->id != 1 || !is_entered)
	{
		is_entered = true;
		pthread_join(tp->thread, NULL);
		tp = tp->right_philo;
	}
}

int	execute(char **argv)
{
	t_data	dat;
	t_philo	*philo;

	if (init_data(&dat, argv) == false)
		return (EXIT_FAILURE);
	philo = init_philo(&dat);
	if (!philo)
		return (EXIT_FAILURE);
	wait_all_philo(philo);
	join_all_philo(philo);
	free_philo(philo);
	return (EXIT_SUCCESS);
}
