/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:21:45 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/28 21:15:38 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philosopher	*philosopher_create(int n_philosophers)
{
	t_philosopher	*philosophers;
	int				i;

	philosophers = ft_calloc(n_philosophers, sizeof(t_philosopher));
	if (!philosophers)
		return (NULL);
	i = 0;
	while (i < n_philosophers)
	{
		philosophers[i].id = i + 1;
		philosophers[i].fork_left = i;
		philosophers[i].fork_right = (i + 1) % n_philosophers;
		++i;
	}
	return (philosophers);
}

t_program	*rules_init(int argc, char **argv)
{
	t_program		*program;

	if (is_all_numbers(argc - 1, &argv[1]) == FALSE)
		return (NULL);
	program = ft_calloc(1, sizeof(t_program));
	if (!program)
		return (NULL);
	program->rules.n_philosophers = ft_atoi(argv[1]);
	program->rules.time_to_die = ft_atoi(argv[2]);
	program->rules.time_to_eat = ft_atoi(argv[3]);
	program->rules.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		program->rules.n_times_must_eat = ft_atoi(argv[5]);
	return (program);
}

t_program	*philosophers_init(int argc, char **argv)
{
	t_program	*program;

	program = rules_init(argc, argv);
	if (!program)
		return (NULL);
	program->locks.fork_lock = ft_calloc(
			program->rules.n_philosophers,
			sizeof(pthread_mutex_t));
	if (!program->locks.fork_lock)
		return (philosophers_destroy(program), NULL);
	program->all.threads = ft_calloc(program->rules.n_philosophers,
			sizeof(pthread_t));
	if (!program->all.threads)
		return (philosophers_destroy(program), NULL);
	program->all.philos = philosopher_create(program->rules.n_philosophers);
	if (!program->all.philos)
		return (philosophers_destroy(program), NULL);
	return (program);
}

void	philosophers_destroy(t_program *program)
{
	if (!program)
		return ;
	if (program->locks.fork_lock)
		free(program->locks.fork_lock);
	if (program->all.threads)
		free(program->all.threads);
	if (program->all.philos)
		free(program->all.philos);
	free(program);
}
