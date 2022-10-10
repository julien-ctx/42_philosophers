/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_must_eat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:47:22 by jcauchet          #+#    #+#             */
/*   Updated: 2022/06/04 14:46:43 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	print_must_eat(void)
{
	printf("\e[1;37m");
	printf("\nEverybody has eaten enough!\n\n");
	printf("\033[0m");
}

void	checker_e_loop(t_args *args)
{
	int				i;
	int				total;
	int				sum;

	total = args->total;
	while (1)
	{
		i = -1;
		sum = 0;
		while (++i < total)
		{
			pthread_mutex_lock(&args->philos[i].eat_count);
			if (args->philos[i].has_eaten >= args->must_eat)
				sum++;
			pthread_mutex_unlock(&args->philos[i].eat_count);
		}
		if (sum == args->total)
		{
			pthread_mutex_lock(&args->print);
			print_must_eat();
			pthread_mutex_unlock(&args->death);
			return ;
		}
	}
}

void	*checker_e_handler(void *args)
{
	checker_e_loop(((t_args *)args));
	return (NULL);
}
