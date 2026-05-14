/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amweyer <amweyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:25:50 by amweyer           #+#    #+#             */
/*   Updated: 2025/09/24 12:21:25 by amweyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "stdio.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (init_data(ac, av, &data))
		return (1);
	if (threads_routine(&data))
	{
		clean_all(&data);
		return (1);
	}
	clean_all(&data);
	return (0);
}
