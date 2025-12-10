#include "../include/philo.h"
#include <pthread.h>
#include <stdlib.h>

int		take_forks(t_philo *philo);
int		put_down_forks(t_philo *philo);

int		take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(philo->left_fork) != 0)
			return (EXIT_FAILURE);
		print_state(philo, philo->id, "has taken a fork", DONT_UPDATE);
		if (pthread_mutex_lock(philo->right_fork) != 0)
			return (EXIT_FAILURE);
		print_state(philo, philo->id, "has taken a fork", DONT_UPDATE);
	}
	else
	{
		if (pthread_mutex_lock(philo->right_fork) != 0)
			return (EXIT_FAILURE);
		print_state(philo, philo->id, "has taken a fork", DONT_UPDATE);
		if (pthread_mutex_lock(philo->left_fork) != 0)
			return (EXIT_FAILURE);
		print_state(philo, philo->id, "has taken a fork", DONT_UPDATE);
	}
	return (EXIT_SUCCESS);
}

int	put_down_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_unlock(philo->left_fork) != 0)
			return (EXIT_FAILURE);
		if (pthread_mutex_unlock(philo->right_fork) != 0)
			return (EXIT_FAILURE);
	}
	else
	{
		if (pthread_mutex_unlock(philo->right_fork) != 0)
			return (EXIT_FAILURE);
		if (pthread_mutex_unlock(philo->left_fork) != 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	philo_eat(t_philo *philo)
{
	//if (philo->allowed_to_eat == FALSE)
	//	return (EXIT_FAILURE);
	if (philo->table->stop_meal == TRUE)
		return (EXIT_FAILURE);
	if (take_forks(philo) != 0)
		return (EXIT_FAILURE);
	print_state(philo, philo->id, "is eating", UPDATE_LAST_MEAL);
	usleep(philo->table->rules.time_to_eat * 1000);
	if (put_down_forks(philo) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
