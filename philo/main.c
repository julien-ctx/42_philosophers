/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 15:13:24 by jcauchet          #+#    #+#             */
/*   Updated: 2022/06/04 13:22:26 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	argument_checker(int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
	{
		printf("Error: wrong number of arguments.\n");
		return (1);
	}
	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) <= 0)
		{
			printf("Error: bad number format\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	mutex_init(t_thread *philos, t_args *args)
{
	int				i;
	unsigned int	origin;
	struct timeval	start;

	i = 0;
	pthread_mutex_init(&args->death, NULL);
	pthread_mutex_lock(&args->death);
	gettimeofday(&start, NULL);
	origin = start.tv_sec * 1000 + start.tv_usec / 1000;
	while (i < args->total)
	{
		pthread_mutex_init(&philos[i].fork, NULL);
		pthread_mutex_init(&philos[i].m_last_eat, NULL);
		pthread_mutex_init(&philos[i].eat_count, NULL);
		philos[i].origin = origin;
		philos[i].fork_owner = -1;
		philos[i].has_eaten = 0;
		gettimeofday(&philos[i].last_eat, NULL);
		i++;
	}
	pthread_mutex_init(&args->eat, NULL);
	pthread_mutex_init(&args->print, NULL);
}

void	ft_init(t_thread *philos, t_args *args, char **av, int ac)
{
	int	i;
	int	total;

	total = ft_atoi(av[1]);
	args->total = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	i = -1;
	if (ac == 6)
		args->must_eat = ft_atoi(av[5]);
	else
		args->must_eat = -1;
	while (++i < total)
	{
		if (i == total - 1)
			philos[i].next = philos;
		else
			philos[i].next = &philos[i + 1];
		philos[i].args = args;
		philos[i].i = i;
	}
	mutex_init(philos, args);
}

void	ft_create(t_thread *philos, t_args *args)
{
	int	total;
	int	i;

	total = args->total;
	i = -1;
	while (++i < total)
	{
		pthread_create(&philos[i].thread, NULL, thread_handler, &philos[i]);
		usleep(100);
	}
	if (args->total != 1)
		pthread_create(&args->thread, NULL, checker_d_handler, args);
	if (args->must_eat > 0 && args->total != 1)
		pthread_create(&args->thread, NULL, checker_e_handler, args);
	pthread_mutex_lock(&args->death);
}

int	main(int ac, char **av)
{
	static t_thread		*philos;
	static t_args		args;

	if (argument_checker(ac, av))
		return (EXIT_FAILURE);
	philos = malloc(sizeof(t_thread) * ft_atoi(av[1]));
	args.philos = philos;
	ft_init(philos, &args, av, ac);
	ft_create(philos, &args);
	free(philos);
	return (0);
}
