/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:17:52 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/24 19:19:28 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*allocated_ptr;

	allocated_ptr = malloc(size * nmemb);
	if (!allocated_ptr)
		return (NULL);
	memset(allocated_ptr, 0, size * nmemb);
	return (allocated_ptr);
}
