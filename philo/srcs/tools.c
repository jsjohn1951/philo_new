/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:24:46 by wismith           #+#    #+#             */
/*   Updated: 2022/06/05 18:42:56 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	submit_scroll(t_philo *p, char *s)
{
	pthread_mutex_lock(&p->table->death_check);
	if (!p->table->he_dead)
	{
		pthread_mutex_unlock(&p->table->death_check);
		pthread_mutex_lock(&p->table->scroll_protect);
		printf("%lums %d %s\n",
			time_dif(p->table->init_time, timestamp(p->table)),
			p->id, s);
		pthread_mutex_unlock(&p->table->scroll_protect);
	}
	else
		pthread_mutex_unlock(&p->table->death_check);
}

unsigned long	timestamp(t_table *table)
{
	unsigned long	res;

	pthread_mutex_lock(&table->time);
	gettimeofday(&table->tv, NULL);
	pthread_mutex_unlock(&table->time);
	pthread_mutex_lock(&table->time);
	res = (table->tv.tv_sec * 1000) + (table->tv.tv_usec / 1000);
	pthread_mutex_unlock(&table->time);
	return (res);
}

unsigned long	time_dif(unsigned long init, unsigned long current)
{
	return (current - init);
}

void	alarm_clock(unsigned long time, t_philo *p)
{
	unsigned long	current;
	unsigned long	init;
	struct timeval	tv;

	pthread_mutex_lock(&p->table->time);
	gettimeofday(&tv, NULL);
	pthread_mutex_unlock(&p->table->time);
	init = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	current = init;
	while ((current - init) < time)
	{
		if (coffin_awaits(p))
				return ;
		pthread_mutex_lock(&p->table->time);
		gettimeofday(&tv, NULL);
		pthread_mutex_unlock(&p->table->time);
		current = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	}
}
