/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:36:31 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/17 23:57:19 by lhojoon          ###   ########.fr       */
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

t_fork	*init_fork(void)
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
	philo->initialized = false;
	if (pthread_create(&philo->thread, NULL, philo_action, philo) != 0)
		return (free(philo), NULL);
	philo->left_fork = init_fork();
	philo->right_fork = init_fork();
	if (!philo->left_fork || !philo->right_fork)
		return (free(philo), NULL);
	return (philo);
}
