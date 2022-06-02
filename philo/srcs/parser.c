/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:22:05 by wismith           #+#    #+#             */
/*   Updated: 2022/06/02 15:29:11 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *nptr)
{
	size_t	res;
	int		i;

	res = 0;
	i = 0;
	while ((nptr[i] >= 7 && nptr[i] <= 13) || nptr[i] == ' '
		|| nptr[i] == '+')
		i++;
	while (nptr[i] && (nptr[i] >= 48 && nptr[i] <= 57))
		res = (res * 10) + (nptr[i++] - 48);
	if (res > INT_MAX)
		ft_putstr_err("Error!\n\tNUMBER TOO BIG\n");
	return (res);
}

int	num_check(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if ((s[i] < 48 || s[i] > 57) && s[i] != '+')
			ft_putstr_err("Error!\n\tWrung ChBrEkter dereKteB\n");
	return (ft_atoi(s));
}

void	parser(int argc, char **argv, t_table *dinner)
{
	dinner->n_philo = num_check(argv[1]);
	dinner->t_die = num_check(argv[2]);
	dinner->t_eat = num_check(argv[3]);
	dinner->t_sleep = num_check(argv[4]);
	if (argc == 6)
		dinner->must_eat = num_check(argv[5]);
	else
		dinner->must_eat = -1;
}
