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

#include "../include/philo.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*allocated_ptr;

	allocated_ptr = malloc(size * nmemb);
	if (!allocated_ptr)
		return (NULL);
	memset(allocated_ptr, 0, size * nmemb);
	return (allocated_ptr);
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		++len;
	return (len);
}

int	ft_error(char *message)
{
	int	message_len;

	message_len = ft_strlen(message);
	write(2, "Error: ", 7);
	write(2, message, message_len);
	return (1);
}
