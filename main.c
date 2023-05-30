/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbendiou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:01:54 by bbendiou          #+#    #+#             */
/*   Updated: 2023/05/17 10:02:26 by bbendiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int		i;
	long	nbr;

	i = 0;
	nbr = 0;
	if (!str)
		return (-1);
	if (str[i] == '\0')
		return (0);
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = (nbr * 10) + (str[i] - 48);
		i++;
	}
	if (nbr > 2147483647)
		return (-1);
	return (nbr);
}

void	initialize(t_philo *var, char **av, int ac,	t_print *print)
{
	pthread_mutex_t	*forks;
	long int		time_of_creat;
	int				i;

	i = 0;
	time_of_creat = time_now();
	forks = malloc(ft_atoi(av[1]) * sizeof(pthread_mutex_t));
	while (i < ft_atoi(av[1]))
	{
		var[i].time_of_day = time_now();
		var[i].time_to_die = ft_atoi(av[2]);
		var[i].time_to_eat = ft_atoi(av[3]);
		var[i].time_to_sleep = ft_atoi(av[4]);
		var[i].index = i;
		var[i].nbr_eat = ft_atoi(av[5]);
		var[i].nbr_philo = ft_atoi(av[1]);
		var[i].ac = ac;
		var[i].mutex = forks;
		var[i].print = print;
		i++;
	}
}

int	main(int ac, char **av)
{
	pthread_t		*th;
	t_philo			*var;
	t_print			*print;
	int				i;

	if (ac < 5 || ac > 6)
	{
		write (2, "Error: incorrect number of arguments!\n", 37);
		return (0);
	}
	if (check_argument(av))
		return (0);
	if (ft_atoi(av[1]) == 0 || ft_atoi(av[5]) == 0)
		return (0);
	th = malloc(ft_atoi(av[1]) * sizeof(pthread_t));
	var = malloc(ft_atoi(av[1]) * sizeof(t_philo));
	print = malloc(sizeof(t_print));
	pthread_mutex_init(&print->luck, NULL);
	pthread_mutex_init(&print->print, NULL);
	initialize(var, av, ac, print);
	i = -1;
	while (++i < ft_atoi(av[1]))
		pthread_mutex_init(&(var + i)->mutex[i], NULL);
	creat_philo(var, th);
	check_die(var);
}
