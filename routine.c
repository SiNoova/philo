/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 09:57:27 by akoutate          #+#    #+#             */
/*   Updated: 2024/11/23 11:07:21 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	right_fork(t_philo *philo, size_t time)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->data->print);
	if (philo->data->stop_sim == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->data->print);
		return (1);
	}
	time = update_time();
	printf("%lu %i has taken a fork\n",
		(time - philo->data->start), philo->philo_index);
	pthread_mutex_unlock(philo->data->print);
	if (philo->right_fork == philo->left_fork)
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	return (0);
}

int	take_forks(t_philo *philo, size_t time)
{
	if (right_fork(philo, time))
		return (1);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->data->print);
	if (philo->data->stop_sim == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->data->print);
		return (1);
	}
	time = update_time();
	printf("%lu %i has taken a fork\n",
		(time - philo->data->start), philo->philo_index);
	pthread_mutex_unlock(philo->data->print);
	return (0);
}

int	eating(t_philo *philo, size_t time)
{
	time = update_time();
	philo->lst_time_it_ate = time;
	pthread_mutex_lock(philo->data->print);
	if (philo->data->stop_sim == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->data->print);
		return (1);
	}
	printf("%lu %i is eating\n",
		(time - philo->data->start), philo->philo_index);
	pthread_mutex_unlock(philo->data->print);
	philo->eating_counter++;
	ft_usleep(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	if (philo->data->stop_sim == 0)
	{
		pthread_mutex_unlock(philo->data->print);
		return (1);
	}
	return (0);
}

int	sleep_and_think(t_philo *philo, size_t time)
{
	pthread_mutex_lock(philo->data->print);
	if (philo->data->stop_sim == 0)
	{
		pthread_mutex_unlock(philo->data->print);
		return (1);
	}
	time = update_time();
	printf("%lu %i is sleeping\n",
		(time - philo->data->start), philo->philo_index);
	pthread_mutex_unlock(philo->data->print);
	ft_usleep(philo->data->time_to_sleep, philo);
	pthread_mutex_lock(philo->data->print);
	if (philo->data->stop_sim == 0)
	{
		pthread_mutex_unlock(philo->data->print);
		return (1);
	}
	time = update_time();
	printf("%lu %i is thinking\n",
		(time - philo->data->start), philo->philo_index);
	pthread_mutex_unlock(philo->data->print);
	return (0);
}

void	*routine(void *ptr)
{
	t_philo	*philo;
	size_t	time;

	time = 0;
	philo = (t_philo *)ptr;
	if (philo->philo_index % 2)
		ft_usleep(5, philo);
	while (philo->data->stop_sim == 1)
	{
		if (take_forks(philo, time) || eating(philo, time)
			|| sleep_and_think(philo, time))
			return (NULL);
	}
	return (NULL);
}
