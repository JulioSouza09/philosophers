/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:56:36 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/28 21:05:27 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thread_create(t_program *program, t_program *copy)
{
	int				i;

	i = 0;
	while (i < program->rules.n_philosophers)
	{
		copy[i].rules = program->rules;
		copy[i].locks = program->locks;
		copy[i].philosopher = program->all.philos[i];
		if (pthread_create(&program->all.threads[i], NULL,
				thread_monitor, &copy[i]) != 0)
			return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}

int	thread_join(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->rules.n_philosophers)
	{
		if (pthread_join(program->all.threads[i], NULL) != 0)
			return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}
