/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbendiou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:38:03 by bbendiou          #+#    #+#             */
/*   Updated: 2023/05/17 10:38:30 by bbendiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_argument(char **av)
{
	int	y;
	int	x;

	y = 0;
	while (av[++y])
	{
		x = 0;
		while (av[y][x])
		{
			if (av[y][x] < '0' || av[y][x] > '9')
			{
				write (2, "Error!\n", 8);
				return (1);
			}
			x++;
		}
		if (ft_atoi(av[y]) == -1)
		{
			write (1, "Error!\n", 8);
			return (1);
		}
	}
	return (0);
}

void *func_routine(void *philo)
{
    t_philo *var;
    int right_fork;

    var = (t_philo *)philo;
    right_fork = var->index + 1;
    if (right_fork == var->nbr_philo)
        right_fork = 0;
    while (1)
    {
        pthread_mutex_lock(&var->mutex[var->index]);
        print_msg("has taken a fork", var, 0);
        pthread_mutex_lock(&var->mutex[right_fork]);
        print_msg("has taken a fork", var, 0);
        print_msg("is_eating", var, 0);
        pthread_mutex_lock(&var[0].print->luck);
		var->last_meal = time_now();
		if (var->nbr_eat > 0)
			var->nbr_eat--;
		pthread_mutex_unlock(&var[0].print->luck);
		while (time_now() - var->last_meal < var->time_to_eat)
			func_usleep(100);
		pthread_mutex_unlock(&var->mutex[var->index]);
		pthread_mutex_unlock(&var->mutex[right_fork]);
		if (var->nbr_eat == 0)
			return (NULL);
		print_msg("is sleeping", var, 0);
		var->last_sleep = time_now();
	while (time_now() - var->last_sleep < var->time_to_sleep)
		func_usleep(100);
	print_msg("is thinking", var, 0);
    }
    return (NULL);
}

void creat_philo(t_philo *var, pthread_t *th)
{
    int i;
    int philo_id[var->nbr_philo];

    i = 0;
    while (i < var->nbr_philo)
    {
        philo_id[i] = i;
        if (pthread_create(&th[i], NULL, func_routine, &philo_id[i]))
        {
            printf("Error\n");
            return ;
        }
        func_usleep(50);
        i += 2;
    }
    i = 1;
    while (i < var->nbr_philo)
    {
        philo_id[i] = i;
        if (pthread_create(&th[i], NULL, func_routine, &philo_id[i]))
        {
            printf("Error\n");
            return ;
        }
        func_usleep(50);
        i += 2;
    }
    i = 0;
    while (i < var->nbr_philo)
	{
		pthread_detach(th[i]);
		i++;
	}
}

void	print_msg(char *str, t_philo *var, int i)
{
	pthread_mutex_lock(&var->print->print);
	if (i == 1)
	{
		printf("%s%ld ms %d died\n", RED, time_now() - var->time_creat, var->index + 1);
		return ;
	}
	else
	{
		printf("%ld ms %d %s\n", time_now() - var->time_creat, \
			var->index + 1, str);
	}
	pthread_mutex_unlock(&var->print->print);
}

int	check_die(t_philo *var)
{
	int		i;
	int		j;

	while (1)
	{
		i = -1;
		j = 0;
		while (++i < var[0].nbr_philo)
		{
			pthread_mutex_lock(&var[0].print->luck);
			if (var[i].ac == 6 && var[i].nbr_eat == 0)
				j++;
			if (j == var[i].nbr_philo)
				return (0);
			if (time_now() - var[i].last_meal >= var[i].time_to_die)
			{
				print_msg("", var, 1);
				return (0);
			}
			pthread_mutex_unlock(&var[0].print->luck);
		}
	}
	return (0);
}

