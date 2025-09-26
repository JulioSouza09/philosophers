/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:45:34 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/26 16:10:57 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_program	*philosophers;

	if (argc < 5 || argc > 6)
		return (put_usage_error(argv[0]));
	philosophers = philosophers_init(argc, argv);
	if (!philosophers)
		return (put_usage_error(argv[0]));
	int			i;
	int			j;
	int			k;
	pthread_t	*philos;
	t_philosopher	ph[2];

	k = 0;
	while (k < 2)
	{
		ph[k].id = k;
		++k;
	}
	philos = ft_calloc(philosophers->rules.n_philosophers, sizeof(pthread_t));

	i = 0;
	printf("%d\n", philosophers->rules.n_philosophers);
	while (i < philosophers->rules.n_philosophers)
	{
		printf("Creating thread %d, i = %d\n", i, i);
		if (pthread_create(&philos[i], NULL, thread_monitor, &ph[i]) != 0)
			printf("Thread creation failed!\n");	
		++i;
	}
	j = 0;
	while (j < philosophers->rules.n_philosophers)
	{
		if (pthread_join(philos[j], NULL) != 0)
			return (3);
		++j;
	}
	free(philos);
	philosophers_destroy(philosophers);
	return (0);
}
