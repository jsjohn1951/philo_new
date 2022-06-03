/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:04:38 by wismith           #+#    #+#             */
/*   Updated: 2022/06/03 18:48:18 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	feaster(t_philo *p)
{
	int	flag;

	flag = 0;
	if (!p->table->forks[p->l_fork_id] && !p->table->forks[p->r_fork_id]
		&& p->l_fork_id != p->r_fork_id)
		flag = 1;
	if (flag)
	{
		pthread_mutex_lock(&p->table->fork[p->l_fork_id]);
		p->table->forks[p->l_fork_id] = 1;
		submit_scroll(p, "has taken a fork");
		pthread_mutex_lock(&p->table->fork[p->r_fork_id]);
		p->table->forks[p->r_fork_id] = 1;
		submit_scroll(p, "has taken a fork");
		p->num_eatin++;
		submit_scroll(p, "is eating");
		p->last_feast = timestamp(p->table);
		alarm_clock(p->table->t_eat, p);
		p->table->forks[p->r_fork_id] = 0;
		pthread_mutex_unlock(&p->table->fork[p->r_fork_id]);
		p->table->forks[p->l_fork_id] = 0;
		pthread_mutex_unlock(&p->table->fork[p->l_fork_id]);
	}
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
