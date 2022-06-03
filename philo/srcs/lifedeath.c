/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifedeath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 23:18:58 by wismith           #+#    #+#             */
/*   Updated: 2022/06/03 18:56:35 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*brainzzz(void *brain_matter)
{
	t_philo	*p;

	p = (t_philo *) brain_matter;
	p->num_eatin = 0;
	while (!p->table->he_dead)
	{
		if (coffin_awaits(p))
			return (NULL);
		feaster(p);
		if (coffin_awaits(p)
			|| (p->table->must_eat >= 0 && p->num_eatin >= p->table->must_eat))
			return (NULL);
		submit_scroll(p, "is sleeping");
		alarm_clock(p->table->t_sleep, p);
		if (coffin_awaits(p))
			return (NULL);
		submit_scroll(p, "is thinking");
	}
	return (NULL);
}

void	old_age_bummer(t_table *dinner, t_philo *p)
{
	int	i;

	i = -1;
	while (++i < dinner->n_philo)
	{
		if (pthread_join(p[i].thread, NULL))
			ft_putstr_err("Error!\n\tHe just won't die\n");
		// printf("philo %d has eaten %d times\n", p[i].id, p[i].num_eatin);
	}
	i = -1;
	while (++i < dinner->n_philo)
		pthread_mutex_destroy(&dinner->fork[i]);
	pthread_mutex_destroy(&dinner->scroll_protect);
}

void	neuron_def(t_philo *p, t_table *dinner)
{
	int	i;

	i = -1;
	while (++i < dinner->n_philo)
	{
		pthread_mutex_init(&p[i].dont_steal_food, NULL);
		p[i].id = i + 1;
		p[i].l_fork_id = p[i].id;
		p[i].eating = 0;
		p[i].last_feast = timestamp(dinner);
		if (i == 0)
			p[i].r_fork_id = dinner->n_philo;
		else
			p[i].r_fork_id = p[i].id - 1;
		p[i].table = dinner;
		dinner->forks[i] = 0;
	}
}

void	birth_machine(t_table *dinner)
{
	int		i;
	t_philo	*p;

	p = dinner->p;
	i = -1;
	pthread_mutex_init(&dinner->scroll_protect, NULL);
	pthread_mutex_init(&dinner->time, NULL);
	pthread_mutex_init(&dinner->deadly, NULL);
	neuron_def(p, dinner);
	dinner->init_time = timestamp(dinner);
	while (++i < dinner->n_philo)
	{
		if (pthread_mutex_init(&dinner->fork[i], NULL))
			ft_putstr_err("Error!\n\tCan't create locks\n");
		if (pthread_create(&p[i].thread, NULL, brainzzz, &p[i]))
			ft_putstr_err("Error!\n\tSpawner broke\n");
	}
	old_age_bummer(dinner, p);
}
