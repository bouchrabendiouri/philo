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
void	ft_helper(t_philo *var)
{
	print_msg("is sleeping", var, 0);
	my_usleep(var->data->time_to_sleep);
	print_msg("is thinking", var, 0);
}
void *func_routine(void *philo)
{
    t_philo *var;

    var = (t_philo *)philo;
    while (1)
    {
        pthread_mutex_lock(&var->mutex[var->data->index]);
        print_msg("has taken a fork", var, 0);
        pthread_mutex_lock(&var->mutex[(var->data->index + 1) % var->data->nbr_philo]);
        print_msg("has taken a fork", var, 0);
        print_msg("is_eating", var, 0);
		var->data->last_meal = time_now();
		if (var->data->nbr_eat > 0)
			var->data->nbr_eat--;
		my_usleep(var->data->time_to_eat);
		pthread_mutex_unlock(&var->mutex[var->data->index]);
		pthread_mutex_unlock(&var->mutex[(var->data->index + 1) % var->data->nbr_philo]);
		ft_helper(var);
		usleep(100);
    }
    return (NULL);
}
void helper_philo(t_philo *var, pthread_t *th)
{
	int i;

	i = 1;
	 while (i < var->data->nbr_philo)
    {
       var->data[i].time_creat = var->data[0].time_creat;
	   var->data[i].last_meal = var->data[0].time_creat;
        if (pthread_create(&th[i], NULL, func_routine, &var[i]))
        {
            printf("Error\n");
            return ;
        }
        i += 2;
    }
}
void creat_philo(t_philo *var, pthread_t *th)
{
    int i;

    i = 0;
	var->data[i].time_creat = time_now();
    while (i < var->data->nbr_philo)
    {
		var->data[i].time_creat = var->data[0].time_creat;
		var->data[i].last_meal = var->data[0].time_creat;
        if (pthread_create(&th[i], NULL, func_routine, &var[i]))
        {
            printf("Error\n");
            return ;
        }
        i += 2;
    }
    usleep(100);
	helper_philo(var, th);
}

void	print_msg(char *str, t_philo *var, int i)
{
	if (!i)
		pthread_mutex_lock(&var->print->print);
	if (i == 1)
	{
		printf("%s%ld ms %d died\n", RED, time_now() - var->data->time_creat, var->data->index + 1);
		return ;
	}
	else
	{
		printf("%ld ms %d %s\n", time_now() - var->data->time_creat, \
			var->data->index + 1, str);
	}
	pthread_mutex_unlock(&var->print->print);
}

int	check_die(t_philo *var)
{
	int		i;
	int		j;

	(void)var;
	while (1)
	{
		i = -1;
		j = 0;
		while (++i < var->data[0].nbr_philo)
		{
			if (var->data[i].ac == 6 && var->data[i].nbr_eat == 0)
				j++;
			if (j == var->data[i].nbr_philo)
				return (0);
			if (time_now() - var->data[i].last_meal >= var->data[i].time_to_die)
			{
				pthread_mutex_lock(&var->print->print);
				print_msg("", var, 1);
				return (0);
			}
		}
		usleep(100);
	}
	return (0);
}
