/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 17:12:39 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/16 21:21:20 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_data(t_data *dat, char **argv)
{
	dat->num_of_philo = ft_atoi(argv[1]);
	dat->time_to_die = ft_atoi(argv[2]);
	dat->time_to_eat = ft_atoi(argv[3]);
	dat->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		dat->num_of_must_eat = ft_atoi(argv[5]);
	else
		dat->num_of_must_eat = -1;
	dat->is_died = false;
	dat->is_started = false;
	if (pthread_mutex_init(&dat->mutex, NULL) != 0)
	{
		printf("mutex init error\n");
		return (false);
	}
	return (true);
}

static t_fork	*init_fork(void)
{
	t_fork	*fork;

	fork = (t_fork *)malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	if (pthread_mutex_init(&fork->mutex, NULL) != 0)
		return (free(fork), NULL);
	return (fork);
}

t_philo	*init_first_philo(t_data *dat)
{
	t_philo	*philo;

	philo = NULL;
	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->data = dat;
	philo->eat_count = 0;
	philo->id = 1;
	if (pthread_create(&philo->thread, NULL, philo_action, philo) != 0)
		return (free(philo), NULL);
	philo->left_fork = init_fork();
	philo->right_fork = init_fork();
	philo->initialized = false;
	if (!philo->left_fork || !philo->right_fork)
		return (NULL);
	return (philo);
}

static void	func_free_philo_if_error(t_philo *philo)
{
	t_philo	*tp;

	tp = philo;
	while (tp)
	{
		pthread_mutex_destroy(&tp->right_fork->mutex);
		free(tp->right_fork);
		tp = tp->right_philo;
		free(tp->left_philo);
	}
}

t_philo	*init_philo(t_data *dat)
{
	t_philo	*philo;
	t_philo	*tpv;
	t_philo	*tp;
	int		i;

	philo = init_first_philo(dat);
	if (!philo)
		return (NULL);
	i = 1;
	tpv = philo;
	while (i < dat->num_of_philo)
	{
		tp = (t_philo *)malloc(sizeof(t_philo));
		if (!tp)
			return (func_free_philo_if_error(philo), NULL);
		tpv->right_philo = tp;
		tp->initialized = false;
		tp->left_philo = tpv;
		tp->left_fork = tpv->right_fork;
		tp->eat_count = 0;
		tp->id = i + 1;
		tp->left_fork = tpv->right_fork;
		tp->data = dat;
		if (i + 1 == dat->num_of_philo)
			tp->right_fork = philo->left_fork;
		else
		{
			tp->right_fork = init_fork();
			if (!tp->right_fork)
				return (func_free_philo_if_error(philo), NULL);
		}
		if (pthread_create(&tp->thread, NULL, philo_action, tp) != 0)
			return (func_free_philo_if_error(philo), NULL);
		tpv = tp;
		i++;
	}
	tpv->right_philo = philo;
	philo->left_philo = tpv;
	return (philo);
}
