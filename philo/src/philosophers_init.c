/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:21:45 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/24 19:33:13 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_program	*philosophers_init(int argc, char **argv)
{
	t_program	*program;

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

void	philosophers_destroy(t_program *philosophers)
{
	if (philosophers)
		free(philosophers);
}
