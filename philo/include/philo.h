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

typedef unsigned long long	t_timestamp;

typedef struct s_philo
{
	int				id;
	int				meals_count;
	t_timestamp		last_meal;	
	t_timestamp		last_sleep;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	struct s_table	*table;
}	t_philo;

typedef struct s_rules
{
	t_timestamp	time_to_die;
	t_timestamp	time_to_eat;
	t_timestamp	time_to_sleep;
	int			minimum_meals;
}	t_rules;

typedef struct s_table
{
	int				philos_count;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	t_rules			rules;
}	t_table;

void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strlen(char *str);
int		ft_error(char *message);

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
