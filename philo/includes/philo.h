/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:12:43 by lhojoon           #+#    #+#             */
/*   Updated: 2024/05/17 19:28:27 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# define PHILO_TICK_WAIT 0.1

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_data
{
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				num_of_philo;
	int				num_of_must_eat;
	bool			is_died;
	bool			is_started;
	pthread_mutex_t	mutex;
	pthread_mutex_t	print_mutex;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	bool			initialized;
	pthread_t		thread;
	t_data			*data;
	t_fork			*left_fork;
	t_fork			*right_fork;
	struct s_philo	*left_philo;
	struct s_philo	*right_philo;
}					t_philo;

int				ft_atoi(const char *str);
int				execute(char **argv);
t_philo			*init_philo(t_data *dat);
bool			init_data(t_data *dat, char **argv);
void			*philo_action(void *arg);
unsigned long	get_timestamp(void);
bool			take_forks(t_philo *arg, bool is_even);
void			wait_start(t_philo *philo);
bool			ph_eat(t_philo *arg, unsigned long *last_eat);
void			ph_sleep(t_philo *arg);
bool			check_same_args(t_philo *arg);
bool			ft_usleep(unsigned long time, t_data *dat);
bool			check_died(t_philo *arg, unsigned long last_eat);
bool			check_died_noprint(t_philo *arg, unsigned long last_eat);
t_philo			*init_first_philo(t_data *dat);
t_fork			*init_fork(void);
void			free_philo(t_philo *philo);

#endif