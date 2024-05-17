/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:41:25 by lhojoon           #+#    #+#             */
/*   Updated: 2024/05/17 19:47:26 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo(t_philo *philo)
{
	t_philo	*next;

	if (philo->right_philo->id == 1)
	{
		free(philo->left_fork);
		free(philo->right_fork);
		free(philo);
		return ;
	}
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
