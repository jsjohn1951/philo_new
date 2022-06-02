/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:04:38 by wismith           #+#    #+#             */
/*   Updated: 2022/06/01 18:52:05 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	feaster(t_philo *p)
{
	if (!p->table->forks[p->l_fork_id] && !p->table->forks[p->r_fork_id])
	{
		pthread_mutex_lock(&p->table->fork[p->l_fork_id]);
		p->table->forks[p->l_fork_id] = 1;
		submit_scroll(p, "has taken a fork");
		if (p->l_fork_id != p->r_fork_id)
		{
			pthread_mutex_lock(&p->table->fork[p->r_fork_id]);
			p->table->forks[p->r_fork_id] = 1;
			submit_scroll(p, "has taken a fork");
			submit_scroll(p, "is eating");
			p->last_feast = timestamp(p->table);
			alarm_clock(p->table->t_eat);
			p->table->forks[p->r_fork_id] = 0;
			pthread_mutex_unlock(&p->table->fork[p->r_fork_id]);
		}
		p->table->forks[p->l_fork_id] = 0;
		pthread_mutex_unlock(&p->table->fork[p->l_fork_id]);
	}
}

int	coffin_awaits(t_philo *p)
{
	if (time_dif(p->last_feast, timestamp(p->table)) > p->table->t_die)
	{
		submit_scroll(p, "died");
		pthread_mutex_lock(&p->table->deadly);
		p->table->he_dead = 1;
		pthread_mutex_unlock(&p->table->deadly);
		return (1);
	}
	return (0);
}
