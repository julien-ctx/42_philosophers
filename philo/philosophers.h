/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcauchet <jcauchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:49:05 by jcauchet          #+#    #+#             */
/*   Updated: 2022/06/04 14:54:40 by jcauchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>
# include <string.h>

# define EAT		2
# define STARVING	3
# define FORK		4
# define THINK		5
# define SLEEP		6
# define DIE		7
# define NEXT		8
# define OWN		9
# define LOCK		10
# define UNLOCK		11

typedef struct thread
{
	pthread_t			thread;
	pthread_mutex_t		fork;
	pthread_mutex_t		m_last_eat;
	pthread_mutex_t		eat_count;	
	struct timeval		last_eat;
	struct thread		*next;
	struct args			*args;
	int					i;
	int					fork_owner;
	int					has_eaten;
	unsigned int		origin;
}	t_thread;

typedef struct args
{
	pthread_t			thread;
	pthread_mutex_t		death;
	pthread_mutex_t		print;
	pthread_mutex_t		eat;
	t_thread			*philos;
	struct timeval		end;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat;
	int					total;
}	t_args;

int				ft_atoi(const char *str);
int				error(void);
void			*checker_d_handler(void *args);
void			*checker_e_handler(void *args);
void			*thread_handler(void *args);
unsigned int	time_diff(unsigned int origin, struct timeval *end);
unsigned int	struct_time_diff(struct timeval *s, struct timeval *e);
void			printer(char *msg, unsigned int time, int philo, int color);
void			eat_printer(unsigned int time, int philo, int times);
void			eating(t_thread *args);
void			take_one_fork(t_thread *args, t_thread *next);
int				take_forks(t_thread *args);
void			sleeping(t_thread *args);

#endif
