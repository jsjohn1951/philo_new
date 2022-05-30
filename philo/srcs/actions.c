/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:04:38 by wismith           #+#    #+#             */
/*   Updated: 2022/05/30 11:19:56 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	feaster(t_philo *p)
{
	pthread_mutex_lock(&p->table->fork[p->l_fork_id]);
	submit_scroll(p, "has taken a fork");
	pthread_mutex_lock(&p->table->fork[p->r_fork_id]);
	submit_scroll(p, "has taken a fork");
	submit_scroll(p, "is eating");
	alarm_clock(p->table->t_eat);
	p->last_feast = timestamp(p->table);
	pthread_mutex_unlock(&p->table->fork[p->l_fork_id]);
	pthread_mutex_unlock(&p->table->fork[p->r_fork_id]);
}
