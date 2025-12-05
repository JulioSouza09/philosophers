#include "../include/philo.h"

int		take_forks(t_philo *philo);
int		put_down_forks(t_philo *philo);
int		print_state(int philo_id, char *action, int update);

int	philo_eat(t_philo *philo)
{
	if (take_forks(philo) != 0)
		return (EXIT_FAILURE);
	print_state(philo->id, "eating", UPDATE_LAST_MEAL);
	usleep(philo->table->rules.time_to_eat);
	if (put_down_forks(philo) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
