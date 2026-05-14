/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amweyer <amweyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:31:18 by amweyer           #+#    #+#             */
/*   Updated: 2025/09/25 15:11:41 by amweyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(int ac, char **av, t_data *data)
{
	if (parse(ac, av, data))
		return (1);
	if (init_mutex(&data->dead_lock))
		return (1);
	if (init_mutex(&data->meal_lock))
		return (1);
	if (init_mutex(&data->write_lock))
		return (1);
	if (init_forks(data))
		return (1);
	if (init_philos(data))
		return (1);
	return (0);
}

int	parse(int ac, char **av, t_data *data)
{
	if (validate_args(ac, av))
		return (1);
	data->num_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->num_times_to_eat = ft_atoi(av[5]);
	else
		data->num_times_to_eat = -1;
	data->dead_flag = false;
	return (0);
}

int	validate_args(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("./philo num_phil t_die t_eat t_sleep [num_times_eat]\n");
		return (1);
	}
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > MAX_PHILO)
	{
		printf("Invalid number of philosophers\n");
		return (1);
	}
	if (ft_atoi(av[2]) < 1 || ft_atoi(av[3]) < 1 || ft_atoi(av[4]) < 1)
	{
		printf("Times must be positive integers\n");
		return (1);
	}
	if (ac == 6 && ft_atoi(av[5]) < 0)
	{
		printf("num_times_to_eat must be >= 0\n");
		return (1);
	}
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	i = -1;
	data->philos = malloc((data->num_of_philos + 1) * sizeof(t_philo));
	if (!data->philos)
		return (printf("Philos allocation failed\n"), 1);
	while (++i < data->num_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].num_of_philos = data->num_of_philos;
		data->philos[i].eating = 0;
		data->philos[i].meals_eaten = 0;
		data->philos[i].dead = &data->dead_flag;
		data->philos[i].start_time = get_current_time();
		data->philos[i].last_meal = data->philos[i].start_time;
		data->philos[i].write_lock = &data->write_lock;
		data->philos[i].meal_lock = &data->meal_lock;
		data->philos[i].dead_lock = &data->dead_lock;
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[(i + 1) % data->num_of_philos];
		data->philos[i].time_to_die = data->time_to_die;
		data->philos[i].time_to_eat = data->time_to_eat;
		data->philos[i].time_to_sleep = data->time_to_sleep;
	}
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc((data->num_of_philos) * sizeof(pthread_mutex_t));
	if (!data->forks)
	{
		clean_error(data, "Forks allocation failed\n");
		return (1);
	}
	while (i < data->num_of_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (0);
}
