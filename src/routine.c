/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amweyer <amweyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:04:07 by amweyer           #+#    #+#             */
/*   Updated: 2025/09/25 15:16:42 by amweyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	threads_routine(t_data *data)
{
	int			j;
	pthread_t	monitor;

	j = 0;
	if (choose_routine(data))
		return (clean_error(data, "Error with the thread creation"), 1);
	if (data->num_of_philos != 1)
	{
		if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
			return (clean_error(data, "Error with the thread creation"), 1);
	}
	while (j < data->num_of_philos)
	{
		pthread_join(data->philos[j].thread, NULL);
		j++;
	}
	if (data->num_of_philos != 1)
		pthread_join(monitor, NULL);
	return (0);
}

int	choose_routine(t_data *data)
{
	int	i;

	i = 0;
	if (data->num_of_philos == 1)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_solo_routine,
				(void *)&data->philos[i]) != 0)
			return (1);
	}
	else
	{
		while (i < data->num_of_philos)
		{
			if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
					(void *)&data->philos[i]) != 0)
				return (1);
			i++;
		}
	}
	return (0);
}

void	*philo_routine(void *input)
{
	t_philo	*philo;

	philo = (t_philo *)input;
	if (philo->id % 2 == 1)
		usleep(0.75 * philo->time_to_eat * 1000);
	while (!check_dead(philo))
	{
		if (eat(philo))
			break ;
		if (nap(philo))
			break ;
		if (thinking(philo))
			break ;
	}
	return (NULL);
}

void	*monitor_routine(void *input)
{
	t_data	*data;

	data = (t_data *)input;
	while (1)
	{
		if (is_philo_dead(data))
			return (NULL);
		if (data->num_times_to_eat != -1 && have_philos_finish(data))
		{
			pthread_mutex_lock(&data->dead_lock);
			data->dead_flag = true;
			pthread_mutex_unlock(&data->dead_lock);
			return (NULL);
		}
		usleep(100);
	}
}

void	*philo_solo_routine(void *input)
{
	t_philo	*philo;

	philo = (t_philo *)input;
	if (print_status(philo, "has taken a fork"))
		return (NULL);
	usleep(1000 * philo->time_to_die);
	if (print_status(philo, "died"))
		return (NULL);
	return (NULL);
}
