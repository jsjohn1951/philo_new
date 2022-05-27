/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifedeath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 23:18:58 by wismith           #+#    #+#             */
/*   Updated: 2022/05/27 18:39:53 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*brainzzz(void *brain_matter)
{
	t_philo	*p;

	p = (t_philo *) brain_matter;
	printf("%d spawned\n", p->id);
	usleep(1000);
	printf("thread\n");
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
}

void	neuron_def(t_philo *p, t_table *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->n_philo)
	{
		p[i].id = i + 1;
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
