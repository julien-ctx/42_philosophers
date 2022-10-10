/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 18:18:27 by jcauchet          #+#    #+#             */
/*   Updated: 2022/06/01 17:48:38 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	eat_printer(unsigned int time, int philo, int times)
{
	printf("\e[1;31m");
	printf("⌛ %d", (int)time);
	printf("\t");
	printf("🤵 %d", philo);
	printf("\t");
	printf("has eaten %d times\n", times);
	printf("\033[0m");
}

void	printer(char *msg, unsigned int time, int philo, int color)
{
	if (color == FORK)
		printf("\e[1;35m");
	else if (color == EAT)
		printf("\e[1;36m");
	else if (color == SLEEP)
		printf("\e[1;37m");
	else if (color == DIE)
		printf("\e[1;31m");
	else if (color == THINK)
		printf("\e[1;34m");
	printf("⌛ %d", (int)time);
	printf("\t");
	printf("🤵 %d", philo);
	printf("\t");
	printf("%s\n", msg);
	printf("\033[0m");
}
