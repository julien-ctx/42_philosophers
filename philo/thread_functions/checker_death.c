/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_death.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:17:35 by juliencauch       #+#    #+#             */
/*   Updated: 2022/06/04 15:31:02 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	dying(t_args *args, struct timeval *end, int i)
{
	printer("died", time_diff(args->philos->origin,
			end), args->philos[i].i + 1, DIE);
	pthread_mutex_unlock(&args->death);
	return (1);
}

void	lock_unlock(t_args *args, int choice)
{
	if (choice == LOCK)
	{
		pthread_mutex_lock(&args->print);
		pthread_mutex_lock(&args->eat);
	}
	else if (choice == UNLOCK)
	{
		pthread_mutex_unlock(&args->print);
		pthread_mutex_unlock(&args->eat);
	}
}

int	checker_d_loop(t_args *args)
{
	int				i;
	int				total;

	total = args->total;
	while (1)
	{
		i = -1;
		while (++i < total)
		{
			pthread_mutex_lock(&args->philos[i].m_last_eat);
			if ((int)struct_time_diff(&args->philos[i].last_eat, &args->end)
				>= args->time_to_die)
			{
				usleep(3000);
				lock_unlock(args, LOCK);
				if (args->philos[i].fork_owner
					== args->philos[i].next->fork_owner && args->total != 2)
					lock_unlock(args, UNLOCK);
				else
					return (dying(args, &args->end, i));
			}
			pthread_mutex_unlock(&args->philos[i].m_last_eat);
		}
	}
}

void	*checker_d_handler(void *args)
{
	checker_d_loop(((t_args *)args));
	return (NULL);
}
