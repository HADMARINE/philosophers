/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:01:59 by lhojoon           #+#    #+#             */
/*   Updated: 2024/06/03 18:16:30 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_timestamp(void)
{
	struct timeval	tv;
	unsigned long	ret;

	gettimeofday(&tv, NULL);
	ret = (unsigned long)tv.tv_sec * 1000;
	ret += (unsigned long)tv.tv_usec / 1000;
	return (ret);
}

bool	ft_usleep(unsigned long time, t_data *dat)
{
	unsigned long	start;
	bool			is_died;

	start = get_timestamp();
	while (get_timestamp() - start < time)
	{
		pthread_mutex_lock(&dat->mutex);
		is_died = dat->is_died;
		pthread_mutex_unlock(&dat->mutex);
		if (is_died == true)
			return (false);
		usleep(PHILO_TICK_WAIT * 1000);
	}
	return (true);
}

bool	ft_usleep_v(unsigned long time, t_data *dat, unsigned long last_eat)
{
	unsigned long	start;
	bool			is_died;
	unsigned int	ttd;

	start = get_timestamp();
	while (get_timestamp() - start < time)
	{
		pthread_mutex_lock(&dat->mutex);
		is_died = dat->is_died;
		ttd = dat->time_to_die;
		pthread_mutex_unlock(&dat->mutex);
		if (is_died == true)
			return (false);
		if (last_eat + ttd < get_timestamp())
		{
			pthread_mutex_lock(&dat->mutex);
			dat->is_died = true;
			pthread_mutex_unlock(&dat->mutex);
			return (false);
		}
		usleep(PHILO_TICK_WAIT * 1000);
	}
	return (true);
}
