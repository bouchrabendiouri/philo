/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbendiou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:38:43 by bbendiou          #+#    #+#             */
/*   Updated: 2023/05/17 10:39:01 by bbendiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

# define RED "\033[0;31m"

typedef struct s_print{
	pthread_mutex_t		print;
	pthread_mutex_t		luck;
}	t_print;

typedef struct s_philo{
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    long int last_sleep;
    long int time_of_day;
    int index;
    int nbr_philo;
    int	ac;
    long int last_meal;
    t_print *print;
    long int time_creat;
    int	nbr_eat;
    pthread_mutex_t *mutex;
}   t_philo;

long int time_now(void);
int func_usleep(long int time);
int	check_argument(char **av);
void creat_philo(t_philo *var, pthread_t *th);
void	print_msg(char *str, t_philo *var, int i);
int	check_die(t_philo *var);
int	ft_atoi(char *str);
void	corr_print(char *str, t_philo *var, int i);
void creat_philo(t_philo *var, pthread_t *th);

#endif
