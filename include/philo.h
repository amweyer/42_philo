/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amweyer <amweyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:56:05 by amweyer           #+#    #+#             */
/*   Updated: 2025/09/26 12:12:19 by amweyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define INT_MIN -2147483648
# define INT_MAX 2147483647
# define MAX_PHILO 200

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					num_of_philos;
	int					num_times_to_eat;
	int					dead_flag;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		write_lock;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	t_philo				*philos;
	pthread_mutex_t		*forks;
}						t_data;

typedef struct s_philo
{
	int					id;
	int					eating;
	int					meals_eaten;
	int					num_of_philos;
	int					*dead;
	size_t				last_meal;
	size_t				start_time;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	pthread_t			thread;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*meal_lock;

}						t_philo;

/* parsing.c */
int						init_data(int ac, char **av, t_data *data);
int						parse(int ac, char **av, t_data *data);
int						validate_args(int ac, char **av);
int						init_philos(t_data *data);
int						init_forks(t_data *data);

/* utils.c */
int						ft_atoi(char *arg);
int						init_mutex(pthread_mutex_t *mutex);
int						print_status(t_philo *philo, char *status);
int						check_dead(t_philo *philo);
size_t					get_current_time(void);

/* free.c */
void					clean_all(t_data *data);
void					clean_error(t_data *data, char *msg);

/* routine.c */
int						threads_routine(t_data *data);
void					*philo_routine(void *input);
void					*monitor_routine(void *input);
void					*philo_solo_routine(void *input);
int						choose_routine(t_data *data);

/* routine_utils.c */
int						eat(t_philo *philo);
int						nap(t_philo *philo);
int						thinking(t_philo *philo);
int						myusleep(t_philo *philo, unsigned long time);
int						is_philo_dead(t_data *data);

/* eat_utils.c */
int						safe_unlock(pthread_mutex_t *f1, pthread_mutex_t *f2);
int						take_forks(t_philo *philo);
int						do_eat(t_philo *philo);
int						have_philos_finish(t_data *data);
void					unlock_forks(t_philo *philo);

#endif