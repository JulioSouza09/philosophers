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

#include "../include/philo.h"
#include <pthread.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc < 5 || argc > 6)
		return (ft_error("Invalid arguments"));
	table = create_table(argc, argv);
	if (table == NULL)
		return (ft_error("Could not create table"));
	if (start_meal(table) != 0)
	{
		clean_table(table);
		return (ft_error("Failed initializing threads"));
	}
	if (finish_meal(table->threads, table->philos_count + 1) != 0)
	{
		clean_table(table);
		return (ft_error("Failed joining threads"));
	}
	clean_table(table);
	return (EXIT_SUCCESS);
}
