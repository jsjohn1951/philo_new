/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:57:47 by wismith           #+#    #+#             */
/*   Updated: 2022/06/04 22:06:05 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define KBOLD "\033[1m"
# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"
# define KCLR  "\e[1;1H\e[2J"

struct	s_table;

typedef struct s_philo
{
	int				id;
	int				r_fork_id;
	int				l_fork_id;
	int				eating;
	int				num_eatin;
	unsigned long	last_feast;
	pthread_t		thread;
	struct s_table	*table;
	pthread_mutex_t	dont_steal_food;
}	t_philo;

typedef struct s_table
{
	int				n_philo;
	unsigned long	t_die;
	unsigned long	t_eat;
	int				t_sleep;
	int				must_eat;
	int				he_dead;
	unsigned long	init_time;
	struct timeval	tv;
	int				forks[250];
	t_philo			p[250];
	pthread_mutex_t	fork_mutex[250];
	pthread_mutex_t	deadly;
	pthread_mutex_t	death_check;
	pthread_mutex_t	scroll_protect;
	pthread_mutex_t	food_protect;
	pthread_mutex_t	time;
}	t_table;

/* Parser */
void			parser(int argc, char **argv, t_table *dinner);

/* Error Management */
void			ft_putstr_err(char *s);

/* init */
void			birth_machine(t_table *dinner);

/* tools */
unsigned long	timestamp(t_table *time);
unsigned long	time_dif(unsigned long init, unsigned long current);
void			alarm_clock(unsigned long time, t_philo *p);
void			submit_scroll(t_philo *p, char *s);

/* actions */
void			feaster(t_philo *p);
int				coffin_awaits(t_philo *p);

#endif