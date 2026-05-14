/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amweyer <amweyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 12:52:29 by amweyer           #+#    #+#             */
/*   Updated: 2025/09/25 18:16:20 by amweyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat(t_philo *philo)
{
	if (check_dead(philo))
		return (1);
	if (take_forks(philo))
		return (1);
	if (check_dead(philo))
		return (unlock_forks(philo), 1);
	if (do_eat(philo))
		return (1);
	return (0);
}

int	nap(t_philo *philo)
{
	if (check_dead(philo))
		return (1);
	if (print_status(philo, "is sleeping"))
		return (1);
	usleep(1000 * philo->time_to_sleep);
	return (0);
}

int	thinking(t_philo *philo)
{
	size_t	time2think;

	if (check_dead(philo))
		return (1);
	time2think = (philo->time_to_die - philo->time_to_eat
			- philo->time_to_sleep) / 2;
	if (print_status(philo, "is thinking"))
		return (1);
	if (philo->num_of_philos % 2 == 1)
		usleep(1000 * (time2think));
	return (0);
}

int	is_philo_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_lock(&data->meal_lock);
		if ((get_current_time()
				- data->philos[i].last_meal) >= data->time_to_die)
		{
			pthread_mutex_unlock(&data->meal_lock);
			pthread_mutex_lock(&data->dead_lock);
			data->dead_flag = true;
			pthread_mutex_lock(&data->write_lock);
			printf("%ld %d %s\n", get_current_time(), data->philos[i].id,
				"died");
			pthread_mutex_unlock(&data->write_lock);
			pthread_mutex_unlock(&data->dead_lock);
			return (true);
		}
		pthread_mutex_unlock(&data->meal_lock);
		i++;
	}
	return (false);
}
