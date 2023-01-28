/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:29:07 by mradwan           #+#    #+#             */
/*   Updated: 2023/01/27 21:46:39 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int			i;
	long int	res;
	int			sign;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = sign * -1;
	while (str[i] == '0')
			i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i++] - '0');
		if ((res > 2147483647 && sign == 1) || (res > 2147483648 && sign == -1))
			return (0);
	}
	return (res * sign);
}

long long int current_timestamp(void)
{
    struct timeval te; 
    gettimeofday(&te, NULL);
    long long int milliseconds;
	milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
    return (milliseconds);
}

int	checker_one(int ac, char **av)
{
	int i = 0;
	int j = 1;
	if(ac == 5 || ac == 6)
	{
		while (av[j])
		{
			i = 0;
			while (av[j][i])
			{
				if(av[j][i] >= '0' && av[j][i] <= '9')
					i++;
				else
				{
					printf("invalid\n");
					return(0);
				}
			}
			j++;
		}
	}
	else
	{
		printf("invalid\n");
		return(0);
	}
	i = 1;
	while (i < j)
	{
		if(av[i][0] == '\0')
		{
			printf("invalid\n");
			return(0);
		}
		i++;
	}
	i = 2;
	while (i < j - 1)
	{
		if(ft_atoi(av[1]) > 200 || ft_atoi(av[i]) < 60 || ft_atoi(av[4]) < 60)
		{
			printf("invalid\n");
			return(0);
		}
		i++;
	}
	return(1);
}

void    sleeper(size_t milliseconds)
{
        size_t  start_time;

        start_time = current_timestamp();
        while (current_timestamp() - start_time < milliseconds)
                usleep(50);
}

void	pausing(t_philo *pause)
{
	long long time = current_timestamp();

	while (1)
	{
		if(current_timestamp() - time >= pause->env->time_to_eat)
			break ;
		usleep(500);
	}
}
