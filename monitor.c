/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:45:50 by akoutate          #+#    #+#             */
/*   Updated: 2024/11/23 10:39:29 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_all_philos_ate(t_data data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data.nbr_of_philos)
	{
		if (philos[i].eating_counter >= data.nbr_to_eat)
			i++;
		else
			return (0);
	}
	return (1);
}

void	handle_philosopher_death(t_data *data,
	t_philo *arr, int index, size_t time)
{
	int	i;

	pthread_mutex_lock(data->print);
	data->stop_sim = 0;
	printf("%lu %i died\n", (time - data->start), arr[index].philo_index);
	pthread_mutex_unlock(data->print);
	i = 0;
	while (i < data->nbr_of_philos)
	{
		pthread_join(arr[i].thread, NULL);
		i++;
	}
}

void	handle_all_philos_ate(t_data *data, t_philo *arr)
{
	int	i;

	pthread_mutex_lock(data->print);
	data->stop_sim = 0;
	pthread_mutex_unlock(data->print);
	i = 0;
	while (i < data->nbr_of_philos)
	{
		pthread_join(arr[i].thread, NULL);
		i++;
	}
}

void	monitor_philosophers(t_data *data, t_philo *arr)
{
	size_t	time;
	int		i;

	i = 0;
	while (1)
	{
		time = update_time();
		if (arr[i].lst_time_it_ate && time
			- arr[i].lst_time_it_ate > arr[i].data->time_to_die)
		{
			handle_philosopher_death(data, arr, i, time);
			return ;
		}
		else if (data->nbr_to_eat != -1 && check_if_all_philos_ate(*data, arr))
		{
			handle_all_philos_ate(data, arr);
			return ;
		}
		i++;
		if (i == data->nbr_of_philos)
			i = 0;
	}
}
