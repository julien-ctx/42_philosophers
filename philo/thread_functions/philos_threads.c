/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:06:54 by jcauchet          #+#    #+#             */
/*   Updated: 2022/06/04 15:15:19 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*thread_loop(t_thread *args)
{
	if (args->args->total == 1)
	{
		pthread_mutex_lock(&args->args->print);
		printer("has taken a fork", time_diff(args->origin,
				&args->args->end), args->i, FORK);
		while ((int)time_diff(args->origin, &args->args->end)
			<= args->args->time_to_die)
			usleep(100);
		printer("died", time_diff(args->origin,
				&args->args->end), args->i, DIE);
		pthread_mutex_unlock(&args->args->death);
		return (NULL);
	}
	while (1)
	{
		if (take_forks(args) == EAT)
		{
			eating(args);
			sleeping(args);
		}
	}
	return (NULL);
}

void	*thread_handler(void *args)
{
	thread_loop(((t_thread *)args));
	return (NULL);
}
