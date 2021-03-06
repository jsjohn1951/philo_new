/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:04:38 by wismith           #+#    #+#             */
/*   Updated: 2022/06/05 16:00:45 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	captivity(t_philo *p, int id, int i)
{
	pthread_mutex_lock(&p->table->fork_mutex[id]);
	p->table->forks[id] = i;
	pthread_mutex_unlock(&p->table->fork_mutex[id]);
}

void	feaster(t_philo *p)
{
	pthread_mutex_lock(&p->table->food_protect);
	if (!p->table->forks[p->l_fork_id] && !p->table->forks[p->r_fork_id]
		&& p->l_fork_id != p->r_fork_id)
	{
		pthread_mutex_unlock(&p->table->food_protect);
		captivity(p, p->l_fork_id, 1);
		submit_scroll(p, "has taken a fork");
		captivity(p, p->r_fork_id, 1);
		submit_scroll(p, "has taken a fork");
		submit_scroll(p, "is eating");
		p->num_eatin++;
		p->last_feast = timestamp(p->table);
		alarm_clock(p->table->t_eat, p);
		captivity(p, p->l_fork_id, 0);
		captivity(p, p->r_fork_id, 0);
	}
	else
		pthread_mutex_unlock(&p->table->food_protect);
}

int	coffin_awaits(t_philo *p)
{
	if (time_dif(p->last_feast, timestamp(p->table)) >= p->table->t_die + 5)
	{
		submit_scroll(p, "died");
		pthread_mutex_lock(&p->table->deadly);
		p->table->he_dead = 1;
		pthread_mutex_unlock(&p->table->deadly);
		return (1);
	}
	return (0);
}
