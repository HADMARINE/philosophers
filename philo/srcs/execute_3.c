/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:54:35 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/17 21:59:19 by lhojoon          ###   ########.fr       */
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
		ph_eat((t_philo *)arg, &last_eat);
		((t_philo *)arg)->eat_count++;
		ph_sleep((t_philo *)arg);
	}
	return (NULL);
}
