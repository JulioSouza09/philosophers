/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:43:29 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/28 20:59:26 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define TRUE 1
# define FALSE 0
# define ALLOC_FAILURE -1

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philosopher
{
	int	alive;
	int	id;
	int	fork_left;
	int	fork_right;
	int	time_alive;
	int	time_eating;
	int	time_sleeping;
}	t_philosopher;

typedef struct s_rules
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_philosophers;
	int	n_times_must_eat;
}	t_rules;

typedef struct s_locks
{
	pthread_mutex_t	*fork_lock;
	pthread_mutex_t	print_lock;
}	t_locks;

typedef struct s_threads
{
	t_philosopher	*philos;
	pthread_t		*threads;
}	t_threads;

typedef struct s_program
{
	t_threads		all;
	t_rules			rules;
	t_locks			locks;
	t_philosopher	philosopher;
}	t_program;

/***** Error handler *****/
void		ft_putstr_fd(char *str, int fd);
int			put_usage_error(char *program_path);

/***** Parser utils *****/
int			ft_atoi(const char *nptr);
int			is_digit(char c);
int			is_number(char *str);
int			is_all_numbers(int argc, char **argv);

/***** Parser utils *****/
void		*ft_calloc(size_t nmemb, size_t size);

/***** Philosophers init *****/
t_program	*philosophers_init(int argc, char **argv);
void		philosophers_destroy(t_program *philosophers);

/***** Thread routine *****/
void		*thread_monitor(void *arg);

/***** Thread init *****/
int			thread_create(t_program *program, t_program *copy);
int			thread_join(t_program *program);

#endif
