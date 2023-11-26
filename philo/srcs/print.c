/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksongchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:48:02 by ksongchu          #+#    #+#             */
/*   Updated: 2023/11/22 20:48:04 by ksongchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	print_eating(t_env *env, int id, int *ate, unsigned long end_time)
{
	*ate = 1;
	if (get_time() >= end_time)
		return ;
	pthread_mutex_lock(&env->output);
	printf("\033[0;33m%lu %d has taken a fork\n\033[0m", \
		get_dif_time(env->base_time), id);
	printf("\033[0;33m%lu %d has taken a fork\n\033[0m", \
		get_dif_time(env->base_time), id);
	printf("\033[0;32m%lu %d is eating\n\033[0m", \
		get_dif_time(env->base_time), id);
	pthread_mutex_unlock(&env->output);
}

void	print_dead(t_env *env, int id, unsigned long end_time)
{
	pthread_mutex_lock(&env->dead_notice);
	if (env->stop_work == 0)
	{
		ft_usleep_till(end_time, env);
		env->stop_work = 1;
		pthread_mutex_lock(&env->output);
		printf("\033[0;31m%lu %d has dead\n\033[0m", \
			get_dif_time(env->base_time), id);
		pthread_mutex_unlock(&env->output);
	}
	pthread_mutex_unlock(&env->dead_notice);
}

void	print_think(t_env *env, int id, unsigned long end_time)
{
	if (env->stop_work == 0 && get_dif_time(end_time) != 0)
	{
		pthread_mutex_lock(&env->output);
		printf("\033[0;37m%lu %d is thinking\033[0m\n", \
			get_dif_time(env->base_time), id);
		pthread_mutex_unlock(&env->output);
	}
}

void	print_sleep(t_env *env, int id)
{
	pthread_mutex_lock(&env->output);
	printf("\033[0;34m%lu %d is sleeping\033[0m\n", \
		get_dif_time(env->base_time), id);
	pthread_mutex_unlock(&env->output);
}
