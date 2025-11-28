/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:45:34 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/11/28 15:41:36 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_program	*program;

	if (argc < 5 || argc > 6)
		return (put_usage_error(argv[0]));
	program = philosophers_init(argc, argv);
	if (!program)
		return (put_usage_error(argv[0]));
	return (0);
}
