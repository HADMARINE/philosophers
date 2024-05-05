/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:41:25 by lhojoon           #+#    #+#             */
/*   Updated: 2024/05/05 18:48:12 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo(t_philo *philo)
{
	t_philo	*next;

	philo = philo->right_philo;
	while (philo->id != 1)
	{
		next = philo->right_philo;
		free(philo->right_fork);
		free(philo);
		philo = next;
	}
	free(philo->right_fork);
	free(philo);
}
