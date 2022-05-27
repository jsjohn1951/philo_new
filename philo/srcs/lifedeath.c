/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifedeath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 23:18:58 by wismith           #+#    #+#             */
/*   Updated: 2022/05/27 14:16:37 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*brainzzz(void *brain_matter)
{
	(void) brain_matter;
	printf("spawned\n");
	usleep(500);
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

void	birth_machine(t_table *dinner)
{
	int		i;
	t_philo	*p;

	p = dinner->p;
	i = 0;
	pthread_mutex_init(&dinner->scroll_protect, NULL);
	pthread_mutex_init(&dinner->dont_touch_my_food, NULL);
	while (i < dinner->n_philo)
	{
		if (pthread_mutex_init(&dinner->fork[i], NULL))
			ft_putstr_err("Error!\n\tCan't create locks\n");
		if (pthread_create(&p[i].thread, NULL, brainzzz, &p[i]))
			ft_putstr_err("Error!\n\tSpawner broke\n");
		i++;
	}
	old_age_bummer(dinner, p);
}
