/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:58:06 by mradwan           #+#    #+#             */
/*   Updated: 2023/01/27 20:28:01 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	free_every_thing(t_philo *all, t_env *data)
// {
// 	int i;
// 	i = -1;
// 	while (++i < data->num_of_philo)
// 		pthread_mutex_destroy(&data->forks[i]);
// 	i = -1;
// 	while (++i < data->num_of_philo)
// 		pthread_detach(all[i].philo);
// 	free(data->forks);
// 	free(data);
// 	free(all);
// }

void	free_every_thing(t_philo **all, t_env *data)
{
	int i;
	i = -1;
	t_philo *init;
	init = *all;
	int num = data->num_of_philo;
	i = -1;
	while (++i < data->num_of_philo)
		pthread_detach(init[i].philo);
	i = -1;
	while (++i < num)
		pthread_mutex_destroy(&init[i].env->forks[i]);
	pthread_mutex_destroy(init->env->death_lock);
	free(data->forks);
	free(data->death_lock);
	free(data);
	free(init);
}