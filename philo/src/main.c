/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:45:34 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/25 19:56:30 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	philosopher_sleep(int id)
{
	printf("Philosopher %d is sleeping...\n", id);
}

void	philosopher_eat(int id)
{
	printf("Philosopher %d is eating...\n", id);
}

void	philosopher_think(int id)
{
	printf("Philosopher %d is thinking...\n", id);
}

void	*monitor(void *arg)
{
	int	id;

	id = *(int *)arg + 1;
	philosopher_sleep(id);
	philosopher_eat(id);
	philosopher_think(id);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_program	*philosophers;

	if (argc < 5 || argc > 6)
		return (put_usage_error(argv[0]));
	philosophers = philosophers_init(argc, argv);
	if (!philosophers)
		return (put_usage_error(argv[0]));
	printf("%d\n", philosophers->rules.n_philosophers);
	printf("%d\n", philosophers->rules.time_to_die);
	printf("%d\n", philosophers->rules.time_to_eat);
	printf("%d\n", philosophers->rules.time_to_sleep);
	printf("%d\n", philosophers->rules.n_times_must_eat);

	int			i;
	int			ids[philosophers->rules.n_philosophers];
	pthread_t	*philos;

	philos = ft_calloc(philosophers->rules.n_philosophers, sizeof(pthread_t));
	i = 0;
	while (i < philosophers->rules.n_philosophers)
	{
		ids[i] = i;
		(void)ids;
		if (pthread_create(&philos[i], NULL, monitor, &i) != 0)
			return (2);
		++i;
	}
	i = 0;
	while (i < philosophers->rules.n_philosophers)
	{
		if (pthread_join(philos[i], NULL) != 0)
			return (3);
		++i;
	}
	free(philos);
	philosophers_destroy(philosophers);
	return (0);
}
