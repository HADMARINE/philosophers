/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:12:39 by lhojoon           #+#    #+#             */
/*   Updated: 2023/12/20 20:59:21 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_start(t_philo *philo)
{
	bool	is_started;

	philo->initialized = true;
	while (true)
	{
		pthread_mutex_lock(&philo->data->mutex);
		is_started = philo->data->is_started;
		pthread_mutex_unlock(&philo->data->mutex);
		if (is_started)
		{
			break ;
		}
	}
}

static void	take_forks(t_philo *arg, bool is_even)
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
}

static void	ph_eat(t_philo *arg, unsigned long *last_eat)
{
	unsigned int	tte;

	pthread_mutex_lock(&arg->data->mutex);
	tte = arg->data->time_to_eat;
	pthread_mutex_unlock(&arg->data->mutex);
	take_forks(arg, true);
	// take_forks(arg, arg->id % 2 == 0);
	*last_eat = get_timestamp();
	printf("%lu %d is eating\n", get_timestamp(), arg->id);
	usleep((unsigned long)(tte * 1000));
	pthread_mutex_unlock(&arg->left_fork->mutex);
	pthread_mutex_unlock(&arg->right_fork->mutex);
}

static void	ph_sleep(t_philo *arg)
{
	unsigned int	tts;

	pthread_mutex_lock(&arg->data->mutex);
	tts = arg->data->time_to_sleep;
	pthread_mutex_unlock(&arg->data->mutex);
	printf("%lu %d is sleeping\n", get_timestamp(), arg->id);
	usleep((unsigned long)(tts * 1000));
	printf("%lu %d is thinking\n", get_timestamp(), arg->id);
}

static bool	check_died(t_philo *arg, unsigned long last_eat)
{
	unsigned long	current_time;
	unsigned int	ttd;

	current_time = get_timestamp();
	pthread_mutex_lock(&arg->data->mutex);
	ttd = arg->data->time_to_die;
	pthread_mutex_unlock(&arg->data->mutex);
	if (current_time - last_eat > (unsigned long)(ttd))
	{
		pthread_mutex_lock(&arg->data->mutex);
		arg->data->is_died = true;
		pthread_mutex_unlock(&arg->data->mutex);
		printf("%lu %d died\n", get_timestamp(), arg->id);
		return (false);
	}
	return (true);
} // check global died

void	*philo_action(void *arg)
{
	unsigned long	last_eat;

	wait_start((t_philo *)arg);
	last_eat = get_timestamp();
	while (true)
	{
		if (check_died((t_philo *)arg, last_eat) == false)
			break ;
		ph_eat((t_philo *)arg, &last_eat);
		((t_philo *)arg)->eat_count++;
		ph_sleep((t_philo *)arg);
	}
	return (NULL);
}

void	wait_all_philo(t_philo *philo)
{
	t_philo	*tp;
	bool	is_entered;
	bool	initialzed;

	tp = philo;
	is_entered = false;
	while (true)
	{
		while (tp->id != 1 || !is_entered)
		{
			is_entered = true;
			initialzed = tp->initialized;
			tp = tp->right_philo;
		}
		if (initialzed == true)
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
	return (EXIT_SUCCESS);
}
