/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:17:26 by jcauchet          #+#    #+#             */
/*   Updated: 2022/06/04 13:23:45 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

unsigned int	struct_time_diff(struct timeval *s, struct timeval *e)
{
	gettimeofday(e, NULL);
	return ((e->tv_sec - s->tv_sec) * 1000 + (e->tv_usec - s->tv_usec) / 1000);
}

unsigned int	time_diff(unsigned int origin, struct timeval *end)
{
	gettimeofday(end, NULL);
	return ((end->tv_sec * 1000 + end->tv_usec / 1000) - origin);
}
