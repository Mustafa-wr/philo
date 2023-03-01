/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routien.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 17:34:51 by mradwan           #+#    #+#             */
/*   Updated: 2023/02/03 15:20:02 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *life)
{
	pthread_mutex_lock(life->env->print);
	printf("%lld philo number %d is sleeping \n", \
		current_timestamp() - life->starting, life->id);
	pthread_mutex_unlock(life->env->print);
	sleeper(life->env->time_to_sleep);
}

void	thinking(t_philo *life)
{
	pthread_mutex_lock(life->env->print);
	printf("%lld philo number %d is thinking \n", \
		current_timestamp() - life->starting, life->id);
	pthread_mutex_unlock(life->env->print);
}

void	eating(t_philo *life)
{
	pthread_mutex_lock(life->env->print);
	printf("%lld philo number %d take the right fork\n", \
		current_timestamp() - life->starting, life->id);
	printf("%lld philo number %d take the left fork\n", \
		current_timestamp() - life->starting, life->id);
	printf("%lld philo number %d is eating \n", \
		current_timestamp() - life->starting, life->id);
	pthread_mutex_unlock(life->env->print);
}

static int	philo_life(t_philo *life)
{
	int	local;

	local = 0;
	if (life->id % 2 == 0)
		locks_the_forks2(life);
	else
		locks_the_forks(life);
	if (lock_the_death(life, local))
		return (unlocks_the_forks(life), 1);
	eating(life);
	pthread_mutex_lock(life->env->timer);
	life->last_time_eat = current_timestamp() - life->starting;
	pthread_mutex_unlock(life->env->timer);
	pausing(life);
	unlocks_the_forks(life);
	if (lock_the_death(life, local))
		return (1);
	sleeping(life);
	if (lock_the_death(life, local))
		return (1);
	thinking(life);
	return (0);
}

void	*routiene(void *s)
{
	t_philo	*life;
	int		i;

	life = (t_philo *)s;
	i = life->num_of_epme;
	while (i != 0)
	{
		if (philo_life(life))
			return (NULL);
		pthread_mutex_lock(life->env->timer);
		i--;
		life->num_of_epme = i;
		pthread_mutex_unlock(life->env->timer);
	}
	return (NULL);
}
