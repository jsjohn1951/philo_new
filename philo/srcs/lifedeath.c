/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifedeath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 23:18:58 by wismith           #+#    #+#             */
/*   Updated: 2022/05/29 22:57:44 by wismith          ###   ########.fr       */
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
	submit_scroll(p, "grabbed a fork");
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
		p[i].eating = 0;
		p[i].last_feast = timestamp(dinner);
		if (i == 0)
			p[i].r_fork_id = dinner->n_philo;
		else
			p[i].r_fork_id = p[i].id - 1;
		p[i].table = dinner;
		i++;
	}
}

void	mortality_check(t_table *dinner)
{
	int	i;
	int	id;

	i = 0;
	while ((!dinner->must_eat || i < dinner->must_eat)
		&& !dinner->he_dead)
	{
		id = 0;
		while (id < dinner->n_philo && !dinner->he_dead)
		{
			if (time_dif(dinner->p[id].last_feast, timestamp(dinner))
				>= dinner->t_die)
			{
				printf("%lu %d died\n",
					time_dif(dinner->p[id].last_feast, timestamp(dinner)),
					id + 1);
				dinner->he_dead = 1;
			}
			id++;
		}
		i++;
	}
}

void	birth_machine(t_table *dinner)
{
	int		i;
	t_philo	*p;

	p = dinner->p;
	i = 0;
	pthread_mutex_init(&dinner->scroll_protect, NULL);
	pthread_mutex_init(&dinner->dont_touch_my_food, NULL);
	pthread_mutex_init(&dinner->time, NULL);
	neuron_def(p, dinner);
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
	mortality_check(dinner);
	old_age_bummer(dinner, p);
}
