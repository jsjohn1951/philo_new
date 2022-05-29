/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:24:46 by wismith           #+#    #+#             */
/*   Updated: 2022/05/29 22:53:12 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	submit_scroll(t_philo *p, char *s)
{
	pthread_mutex_lock(&p->table->scroll_protect);
	printf("%lu %d %s\n", time_dif(p->table->init_time, timestamp(p->table)),
		p->id, s);
	pthread_mutex_unlock(&p->table->scroll_protect);
}

unsigned long	timestamp(t_table *table)
{
	unsigned long	res;

	pthread_mutex_lock(&table->time);
	gettimeofday(&table->tv, NULL);
	res = (table->tv.tv_sec * 1000) + (table->tv.tv_usec / 1000);
	pthread_mutex_unlock(&table->time);
	return (res);
}

unsigned long	time_dif(unsigned long init, unsigned long current)
{
	return (current - init);
}

void	alarm_clock(unsigned long time)
{
	unsigned long	current;
	unsigned long	init;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	init = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	current = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	while ((current - init) < time)
	{
		gettimeofday(&tv, NULL);
		current = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	}
}
