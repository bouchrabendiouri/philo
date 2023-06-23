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

useconds_t time_now(void)
{
    struct timeval now;

    gettimeofday(&now, NULL);
    return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

void    my_usleep(useconds_t time)
{
    useconds_t start_time = time_now();
    usleep((time * 1000) - 20000);
    while (time_now() - start_time < time)
    {
        
    }
}
