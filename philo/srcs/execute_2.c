/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:10:24 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/17 21:54:30 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_same_args(t_philo *arg)
{
	t_philo	*left;
	t_philo	*cur;

	pthread_mutex_lock(&arg->data->mutex);
	cur = arg;
	pthread_mutex_unlock(&arg->data->mutex);
	pthread_mutex_lock(&arg->left_philo->data->mutex);
	left = arg->left_philo;
	pthread_mutex_unlock(&arg->left_philo->data->mutex);
	if (cur == left)
	{
		pthread_mutex_lock(&arg->data->mutex);
		arg->data->is_died = true;
		pthread_mutex_unlock(&arg->data->mutex);
		return (false);
	}
	return (true);
}

bool	take_forks(t_philo *arg, bool is_even)
{
	if (is_even)
	{
		pthread_mutex_lock(&arg->right_fork->mutex);
		pthread_mutex_lock(&arg->left_fork->mutex);
		printf("%lu %d has taken a fork\n", get_timestamp(), arg->id);
	}
	else
	{
		pthread_mutex_lock(&arg->left_fork->mutex);
		pthread_mutex_lock(&arg->right_fork->mutex);
		printf("%lu %d has taken a fork\n", get_timestamp(), arg->id);
	}
	return (true);
}

void	wait_start(t_philo *philo)
{
	bool	is_started;

	pthread_mutex_lock(&philo->data->mutex);
	philo->initialized = true;
	pthread_mutex_unlock(&philo->data->mutex);
	while (true)
	{
		pthread_mutex_lock(&philo->data->mutex);
		is_started = philo->data->is_started;
		pthread_mutex_unlock(&philo->data->mutex);
		if (is_started)
			break ;
	}
}

bool	ph_eat(t_philo *arg, unsigned long *last_eat)
{
	unsigned int	tte;

	pthread_mutex_lock(&arg->data->mutex);
	tte = arg->data->time_to_eat;
	pthread_mutex_unlock(&arg->data->mutex);
	if (take_forks(arg, arg->id % 2 == 0) == false)
		return (false);
	if (check_died(arg, *last_eat) == false)
	{
		pthread_mutex_unlock(&arg->left_fork->mutex);
		pthread_mutex_unlock(&arg->right_fork->mutex);
		return (false);
	}
	*last_eat = get_timestamp();
	printf("%lu %d is eating\n", get_timestamp(), arg->id);
	ft_usleep((unsigned long)(tte), arg->data);
	pthread_mutex_unlock(&arg->left_fork->mutex);
	pthread_mutex_unlock(&arg->right_fork->mutex);
	return (true);
}

void	ph_sleep(t_philo *arg)
{
	unsigned int	tts;

	pthread_mutex_lock(&arg->data->mutex);
	tts = arg->data->time_to_sleep;
	pthread_mutex_unlock(&arg->data->mutex);
	printf("%lu %d is sleeping\n", get_timestamp(), arg->id);
	ft_usleep((unsigned long)(tts), arg->data);
	printf("%lu %d is thinking\n", get_timestamp(), arg->id);
}
