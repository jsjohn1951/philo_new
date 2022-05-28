/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifedeath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 23:18:58 by wismith           #+#    #+#             */
/*   Updated: 2022/05/28 17:46:09 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*brainzzz(void *brain_matter)
{
	t_philo	*p;

	p = (t_philo *) brain_matter;
	printf("%lu %d spawned\n",
		time_dif(p->table->init_time, timestamp(p->table)), p->id);
	alarm_clock(1);
	printf("%lu %d %d is my right fork\n",
		time_dif(p->table->init_time, timestamp(p->table)),
		p->id, p->r_fork_id);
	return (NULL);
}

void	old_age_bummer(t_table *dinner, t_philo *p)
{
	int	i;

	i = 0;
	while (i < dinner->n_philo)
	{
		if (pthread_join(p[i].thread, NULL))
			ft_putstr_err("Error!\n\tHe just won't die\n");
		i++;
	}
	i = 0;
	while (i < dinner->n_philo)
	{
		pthread_mutex_destroy(&dinner->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&dinner->scroll_protect);
	pthread_mutex_destroy(&dinner->dont_touch_my_food);
}

void	neuron_def(t_philo *p, t_table *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->n_philo)
	{
		p[i].id = i + 1;
		p[i].l_fork_id = p[i].id;
		if (i == 0)
			p[i].r_fork_id = dinner->n_philo;
		else
			p[i].r_fork_id = p[i].id - 1;
		p[i].table = dinner;
		i++;
	}
}

void	birth_machine(t_table *dinner)
{
	int		i;
	t_philo	*p;

	p = dinner->p;
	i = 0;
	neuron_def(p, dinner);
	pthread_mutex_init(&dinner->scroll_protect, NULL);
	pthread_mutex_init(&dinner->dont_touch_my_food, NULL);
	dinner->init_time = timestamp(dinner);
	while (i < dinner->n_philo)
	{
		if (pthread_mutex_init(&dinner->fork[i], NULL))
			ft_putstr_err("Error!\n\tCan't create locks\n");
		if (pthread_create(&p[i].thread, NULL, brainzzz, &p[i]))
			ft_putstr_err("Error!\n\tSpawner broke\n");
		usleep(2);
		i++;
	}
	old_age_bummer(dinner, p);
}
