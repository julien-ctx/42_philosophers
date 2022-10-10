/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 14:50:47 by jcauchet          #+#    #+#             */
/*   Updated: 2022/06/04 15:46:23 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	eating(t_thread *args)
{
	unsigned int	now;
	struct timeval	end;

	pthread_mutex_lock(&args->args->print);
	printer("is eating", time_diff(args->origin, &end), args->i + 1, EAT);
	pthread_mutex_unlock(&args->args->print);
	gettimeofday(&end, NULL);
	now = end.tv_sec * 1000 + end.tv_usec / 1000;
	pthread_mutex_lock(&args->m_last_eat);
	gettimeofday(&args->last_eat, NULL);
	pthread_mutex_unlock(&args->m_last_eat);
	pthread_mutex_lock(&args->eat_count);
	args->has_eaten++;
	pthread_mutex_unlock(&args->eat_count);
	while ((int)time_diff(now, &args->args->end) < args->args->time_to_eat)
		usleep(100);
	pthread_mutex_lock(&args->args->print);
	printer("is sleeping", time_diff(args->origin, &end), args->i + 1, SLEEP);
	pthread_mutex_unlock(&args->args->print);
	args->fork_owner = -1;
	args->next->fork_owner = -1;
	pthread_mutex_unlock(&args->fork);
	pthread_mutex_unlock(&args->next->fork);
}

void	take_one_fork(t_thread *args, t_thread *next)
{
	int	time;

	time = (int)time_diff(args->origin, &args->args->end);
	if (next->fork_owner == -1)
	{
		next->fork_owner = args->i;
		pthread_mutex_lock(&next->args->print);
		printer("has taken a fork", time, args->i + 1, FORK);
		pthread_mutex_unlock(&next->args->print);
	}
}

int	take_forks(t_thread *args)
{
	if (args->i % 2 == 0)
	{
		if (!pthread_mutex_lock(&args->next->fork))
			take_one_fork(args, args->next);
		if (!pthread_mutex_lock(&args->fork))
			take_one_fork(args, args);
	}
	else
	{
		usleep(100);
		if (!pthread_mutex_lock(&args->fork))
			take_one_fork(args, args);
		if (!pthread_mutex_lock(&args->next->fork))
			take_one_fork(args, args->next);
	}
	return (EAT);
}

void	sleeping(t_thread *args)
{
	unsigned int	now;
	struct timeval	end;

	gettimeofday(&end, NULL);
	now = end.tv_sec * 1000 + end.tv_usec / 1000;
	while ((int)time_diff(now, &args->args->end) < args->args->time_to_sleep)
		usleep(100);
	pthread_mutex_lock(&args->args->print);
	printer("is thinking", time_diff(args->origin, &end), args->i + 1, THINK);
	pthread_mutex_unlock(&args->args->print);
}
