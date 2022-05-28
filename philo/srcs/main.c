/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:58:01 by wismith           #+#    #+#             */
/*   Updated: 2022/05/28 17:31:31 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_putstr_err(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	write(2, s, i);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_table	dinner;

	if (argc != 5 && argc != 6)
		ft_putstr_err("Error!\n\tWrong number of arguments\n");
	parser(argc, argv, &dinner);
	birth_machine(&dinner);
	return (0);
}
