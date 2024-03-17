/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 17:12:39 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/17 22:18:27 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static bool
	init_philo_values(t_philo *tp, t_philo *tpv, t_philo *philo, void *d[2])
{
	int		i;
	t_data	*dat;

	i = *(int *)d[0];
	dat = (t_data *)d[1];
	tp->initialized = false;
	tpv->right_philo = tp;
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
			return (func_free_philo_if_error(philo), false);
	}
	return (true);
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
		if (init_philo_values(tp, tpv, philo, (void *[]){&i, dat}) == false)
			return (NULL);
		if (pthread_create(&tp->thread, NULL, philo_action, tp) != 0)
			return (func_free_philo_if_error(philo), NULL);
		tpv = tp;
		i++;
	}
	tpv->right_philo = philo;
	philo->left_philo = tpv;
	return (philo);
}
