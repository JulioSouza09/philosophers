#include "../include/philo.h"

int		philo_sleep(t_philo *philo);
int		philo_think(t_philo *philo);
int		print_state(int philo_id, char *action, int update);
long	get_timestamp(void);

int	philo_sleep(t_philo *philo)
{
	print_state(philo->id, "sleeping", UPDATE_LAST_SLEEP);
	usleep(philo->table->rules.time_to_sleep);
	return (EXIT_SUCCESS);
}

int	philo_think(t_philo *philo)
{
	long	timestamp;
	int		time_to_sleep;
	int		last_sleep;

	time_to_sleep = philo->table->rules.time_to_sleep;
	last_sleep = philo->last_sleep;
	timestamp = get_timestamp();
	if (timestamp > last_sleep + time_to_sleep)
		print_state(philo->id, "thinking", DONT_UPDATE);
	return (EXIT_SUCCESS);
}
