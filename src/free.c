/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amweyer <amweyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:04:28 by amweyer           #+#    #+#             */
/*   Updated: 2025/09/25 15:17:35 by amweyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_all(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->forks)
	{
		i = 0;
		while (i < data->num_of_philos)
			pthread_mutex_destroy(&data->forks[i++]);
		free(data->forks);
		data->forks = NULL;
	}
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->write_lock);
}

void	clean_error(t_data *data, char *msg)
{
	if (msg)
		printf("Error: %s\n", msg);
	clean_all(data);
}
