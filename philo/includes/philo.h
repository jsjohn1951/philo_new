/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:57:47 by wismith           #+#    #+#             */
/*   Updated: 2022/05/27 13:03:20 by wismith          ###   ########.fr       */
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
	int				last_feast;
	pthread_t		thread;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	int				he_dead;
	t_philo			p[250];
	pthread_mutex_t	fork[250];
	pthread_mutex_t	scroll_protect;
	pthread_mutex_t	dont_touch_my_food;
}	t_table;

/* Parser */
void	parser(int argc, char **argv, t_table *dinner);

/* Error Management */
void	ft_putstr_err(char *s);

/* init */
void	birth_machine(t_table *dinner);

#endif