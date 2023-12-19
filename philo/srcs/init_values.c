/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 17:12:39 by lhojoon           #+#    #+#             */
/*   Updated: 2023/12/19 18:07:55 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	init_data(char **argv)
{
	t_data	dat;

	dat.num_of_philo = ft_atoi(argv[1]);
	dat.time_to_die = ft_atoi(argv[2]);
	dat.time_to_eat = ft_atoi(argv[3]);
	dat.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		dat.num_of_must_eat = ft_atoi(argv[5]);
	else
		dat.num_of_must_eat = -1;
	dat.is_died = false;
	return (dat);
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
	philo->left_fork = (t_fork *)malloc(sizeof(t_fork));
	philo->right_fork = (t_fork *)malloc(sizeof(t_fork));
	if (!philo->left_fork || !philo->right_fork)
		return (NULL);
	pthread_mutex_init(philo->left_fork->mutex, NULL);
	pthread_mutex_init(philo->right_fork->mutex, NULL);
	return (philo);
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
	while (i <= dat->num_of_philo)
	{
		tp = (t_philo *)malloc(sizeof(t_philo));
		if (!tp)
			return (NULL); // free all philos
		tpv->right_fork = tp;
		tp->id = i + 1;
		tp->eat_count = 0;
		tp->left_fork = tpv->right_fork;
		if (i + 1 == dat->num_of_philo)
			tp->right_fork = philo->left_fork;
		else
			tp->right_fork = (t_fork *)malloc(sizeof(t_fork));
		tpv = tp;
	}
	return (philo);
}
