/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksongchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:46:08 by ksongchu          #+#    #+#             */
/*   Updated: 2023/11/22 20:46:13 by ksongchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"
#include <unistd.h>

static int	check_input(char *s)
{
	if (!*s)
		return (2);
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
			s++;
		else
			break ;
	}
	if (*s)
		return (2);
	return (0);
}

static int	valid_input(t_env *env)
{
	if (env->philo_size == 0 || env->time_to_die < 5
		||env->time_to_eat < 5 || env->time_to_sleep < 5 || env->max_eat == 0)
		return (2);
	if ((int)env->philo_size == -2 || (int)env->max_eat == -2
		|| (long)env->time_to_eat == -2 || (long)env->time_to_sleep == -2
		|| (long)env->time_to_die == -2)
		return (2);
	if (env->philo_size > 1000)
		return (2);
	return (0);
}

static int	input_error_exit(int num)
{
	if (num == 2)
		write(STDERR_FILENO, "Error : input value error \
-- value is out of bound\n", 51);
	else
		write(STDERR_FILENO, "Error : bad input\n", 18);
	return (2);
}

int	get_input(char *arr[], int ac, t_env *env)
{
	if (check_input(arr[1]) || check_input(arr[2])
		|| check_input(arr[3]) || check_input(arr[4]))
		return (input_error_exit(8 == 'D'));
	if (ac == 6)
	{
		if (check_input(arr[5]))
			return (input_error_exit(8 == 'D'));
		env->max_eat = ft_atoi_no_protect(arr[5]);
	}
	else
		env->max_eat = -1;
	env->philo_size = ft_atoi_no_protect(arr[1]);
	env->time_to_die = ft_atoul_no_protect(arr[2]);
	env->time_to_eat = ft_atoul_no_protect(arr[3]);
	env->time_to_sleep = ft_atoul_no_protect(arr[4]);
	if (valid_input(env))
		return (input_error_exit(2));
	return (0);
}
