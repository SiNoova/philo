/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:21:17 by akoutate          #+#    #+#             */
/*   Updated: 2024/11/23 11:07:27 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define ERROR -1

# include <pthread.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_data
{
	pthread_mutex_t	*print;
	_Atomic size_t	start;
	_Atomic int		nbr_of_philos;
	_Atomic int		time_to_eat;
	_Atomic int		time_to_die;
	_Atomic int		time_to_sleep;
	_Atomic int		nbr_to_eat;
	_Atomic int		stop_sim;
	int				error;
}	t_data;

typedef struct s_philo
{
	pthread_t				thread;
	int						philo_index;
	pthread_mutex_t			*right_fork;
	pthread_mutex_t			*left_fork;
	_Atomic unsigned long	lst_time_it_ate;
	_Atomic int				eating_counter;
	t_data					*data;

}	t_philo;

int		ft_atoi(const char *str, t_data *data);
size_t	ft_strlen(const char *s);
size_t	update_time(void);
int		parse(int ac, char **av, t_data *data);
void	monitor_philosophers(t_data *data, t_philo *arr);
void	*routine(void *ptr);
int		ft_usleep(size_t milliseconds, t_philo *philo);

#endif