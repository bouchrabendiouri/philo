/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbendiou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 09:58:22 by bbendiou          #+#    #+#             */
/*   Updated: 2023/05/17 09:59:20 by bbendiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int time_now(void)
{
    struct timeval now;

    gettimeofday(&now, NULL);
    return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

int func_usleep(long int time)
{
    long int start_time;

    start_time = time_now();
    while ((time_now() - start_time) < time)
        usleep(100);
    return (1);
}

