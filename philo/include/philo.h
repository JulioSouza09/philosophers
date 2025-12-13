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

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

enum	e_update
{
	UPDATE_LAST_MEAL,
	UPDATE_LAST_SLEEP,
	DONT_UPDATE
};

typedef unsigned long long	t_timestamp;

typedef struct s_philo
{
	int				id;
	int				meals_count;
	int				allowed_to_eat;
	t_timestamp		last_meal;	
	t_timestamp		last_sleep;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	struct s_table	*table;
}	t_philo;

typedef struct s_rules
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	minimum_meals;
}	t_rules;

typedef struct s_table
{
	int				philos_count;
	int				stop_meal;
	long			start_time;
	t_philo			*philos;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*state_lock;
	t_rules			rules;
}	t_table;

void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strlen(const char *str);
int		ft_error(const char *message);
int		ft_atoi_safe(const char *nptr, int *result);
int		is_valid_number(char *str);

t_table	*create_table(int arg_count, char **argv);
void	clean_table(t_table *table);

int		start_meal(t_table *table);
int		finish_meal(pthread_t *threads, int size);

int		philo_eat(t_philo *philo);
int		take_forks(t_philo *philo);
int		put_down_forks(t_philo *philo);
int		philo_sleep(t_philo *philo);
int		philo_think(t_philo *philo);
int		print_state(t_philo *philo, int philo_id, char *action, int update);
long	get_timestamp(void);

/*
void		ft_putstr_fd(char *str, int fd);
int			put_usage_error(char *program_path);

int			ft_atoi(const char *nptr);
int			is_digit(char c);
int			is_number(char *str);
int			is_all_numbers(int argc, char **argv);

void		*ft_calloc(size_t nmemb, size_t size);

t_program	*philosophers_init(int argc, char **argv);
void		philosophers_destroy(t_program *philosophers);

void		*thread_monitor(void *arg);

int			thread_create(t_program *program, t_program *copy);
int			thread_join(t_program *program);
*/

#endif
