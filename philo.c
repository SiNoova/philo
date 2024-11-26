/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:21:20 by akoutate          #+#    #+#             */
/*   Updated: 2024/11/23 10:53:46 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = update_time();
	while ((update_time() - start) < milliseconds && philo->data->stop_sim == 1)
		usleep(500);
	return (0);
}

void	init_philos(t_data *data, t_philo *arr, size_t time)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philos)
	{
		arr[i].philo_index = i + 1;
		arr[i].data = data;
		arr[i].lst_time_it_ate = time;
		arr[i].eating_counter = 0;
		pthread_create(&arr[i].thread, NULL, routine, &arr[i]);
		i++;
	}
}

int	init(t_data *data, t_philo *arr, int i, size_t time)
{
	pthread_mutex_init(data->print, NULL);
	while (i < data->nbr_of_philos)
	{
		arr[i].right_fork = malloc(sizeof(pthread_mutex_t));
		if (!arr[i].right_fork)
		{
			write (2, "malloc error", 13);
			while (i)
			{
				i--;
				free(arr[i].right_fork);
			}
			return (1);
		}
		pthread_mutex_init(arr[i].right_fork, NULL);
		if (i > 0)
			arr[i].left_fork = arr[i - 1].right_fork;
		i++;
	}
	arr[0].left_fork = arr[data->nbr_of_philos - 1].right_fork;
	init_philos(data, arr, time);
	return (0);
}

void	cleanup(t_data *data, t_philo *arr)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(data->print);
	free(data->print);
	while (i < data->nbr_of_philos)
	{
		pthread_mutex_destroy(arr[i].right_fork);
		free(arr[i].right_fork);
		i++;
	}
	free(arr);
}

int	main(int ac, char **av)
{
	t_data	data;
	size_t	time;
	t_philo	*arr;

	time = update_time();
	data.start = time;
	if (parse(ac, av, &data))
		return (1);
	data.stop_sim = 1;
	data.print = malloc(sizeof(pthread_mutex_t));
	if (!data.print)
		return (1);
	arr = malloc(data.nbr_of_philos * sizeof(t_philo));
	if (!arr)
	{
		write (2, "malloc error", 13);
		free (data.print);
		return (1);
	}
	if (init(&data, arr, 0, time))
		return (1);
	monitor_philosophers(&data, arr);
	cleanup(&data, arr);
}
