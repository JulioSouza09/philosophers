/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:45:34 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/28 20:48:24 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_program	*program;
	t_program	*args;

	if (argc < 5 || argc > 6)
		return (put_usage_error(argv[0]));
	program = philosophers_init(argc, argv);
	if (!program)
		return (put_usage_error(argv[0]));
	args = ft_calloc(program->rules.n_philosophers, sizeof(t_program));
	if (!args)
		return (EXIT_FAILURE);
	if (thread_create(program, args) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (thread_join(program) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (args)
		free(args);
	philosophers_destroy(program);
	return (0);
}
