/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:07:41 by msisto            #+#    #+#             */
/*   Updated: 2024/10/30 14:29:35 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	no_alpha(int ac, char **av)
{
	int	i;
	int	k;

	i = 1;
	while (i < ac)
	{
		k = 0;
		while (av[i][k] != '\0')
		{
			if (av[i][k] < '0' || av[i][k] > '9')
			{
				write(2, "Error\n", 6);
				exit(1);
			}
			k++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	philo_t	*philos;
	table_t	table;
	pthread_mutex_t	*forks;

	if (argc > 6 || argc < 5)
		return(write(2, "Error\n", 6), 1);
	no_alpha(argc, argv);
	philos = malloc(ft_atoi(argv[1]) * sizeof(philo_t));
	if (!philos)
		return (1);
	forks = malloc(ft_atoi(argv[1]) * sizeof(pthread_mutex_t));
	if (!forks)
		return (1);
	table_builder(&table, philos);
	fork_maker(forks, ft_atoi(argv[1]));
	philo_maker(philos, &table, forks, argv);
	thread_create(&table, forks);
	destory_all(&table, forks);
	return (0);
}
