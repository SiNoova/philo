/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:36:40 by akoutate          #+#    #+#             */
/*   Updated: 2024/11/23 11:05:37 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 5 && ac != 6)
	{
		write(2, "Error: invalid number of args!\n", 30);
		return (1);
	}
	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if ((av[i][j] < '0' || av[i][j] > '9')
				&& !(av[i][j] == '+' && j == 0))
			{
				write(2, av[i], ft_strlen(av[i]));
				return (write(2, ": use positive numbers only\n", 29), 1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	init_data(t_data *data, int ac, char **av)
{
	data->error = 0;
	data->nbr_of_philos = ft_atoi(av[1], data);
	data->time_to_die = ft_atoi(av[2], data);
	data->time_to_eat = ft_atoi(av[3], data);
	data->time_to_sleep = ft_atoi(av[4], data);
	if (ac == 6)
		data->nbr_to_eat = ft_atoi(av[5], data);
	else
		data->nbr_to_eat = -1;
}

int	parse(int ac, char **av, t_data *data)
{
	if (print_error(ac, av))
		return (1);
	init_data(data, ac, av);
	if (!data->nbr_of_philos || !data->time_to_die || !data->time_to_eat
		|| !data->time_to_sleep || !data->nbr_to_eat || data->error)
	{
		write (2, "Error: invalid input!\n", 23);
		return (1);
	}
	return (0);
}
