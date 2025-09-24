/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:45:34 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/24 19:42:47 by jcesar-s         ###   ########.fr       */
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
	printf("%d\n", philosophers->rules.n_philosophers);
	printf("%d\n", philosophers->rules.time_to_die);
	printf("%d\n", philosophers->rules.time_to_eat);
	printf("%d\n", philosophers->rules.time_to_sleep);
	printf("%d\n", philosophers->rules.n_times_must_eat);
	philosophers_destroy(philosophers);
	return (0);
}
