/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoutate <akoutate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:36:01 by akoutate          #+#    #+#             */
/*   Updated: 2024/11/23 10:16:23 by akoutate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	strtoint(const char *str, int i, int sign, t_data *data)
{
	unsigned long long	nb;
	int					c;

	nb = 0;
	c = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		c++;
		if (c == 20 || nb > INT_MAX)
		{
			data->error = ERROR;
			return (-1);
		}
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	if (nb > LONG_MAX || nb > INT_MAX)
	{
		data->error = ERROR;
		return (-1);
	}
	return (nb * sign);
}

int	ft_atoi(const char *str, t_data *data)
{
	int		sign;
	size_t	i;

	sign = 1;
	i = 0;
	while ((str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] == '0')
		i++;
	return (strtoint(str, i, sign, data));
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	update_time(void)
{
	struct timeval	current_time;
	size_t			time;

	gettimeofday(&current_time, NULL);
	time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (time);
}
