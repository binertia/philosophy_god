/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksongchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:46:28 by ksongchu          #+#    #+#             */
/*   Updated: 2023/11/22 20:46:30 by ksongchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	*fn_god (void *args)
{
	t_env	*env;
	int		i;

	env = (t_env *)args;
	while (1)
	{
		i = 0;
		pthread_mutex_lock(&env->dead_notice);
		if (env->stop_work)
		{
			usleep(9000);
			clean_out(env);
			break;
		}
		else
		{
			while (env->cycle_end[i] == 0)
				i++;
			if (env->philo_size == i - 1)
			{
				usleep(9000);
				clean_out(env);
				break;
			}
		}
		pthread_mutex_unlock(&env->dead_notice);
		usleep(500);
	}
	return (args);
}

static int	start_thread(t_env *env)
{
	int	i;

	if (init_env(env))
		return (2);
	if (env->philo_size > 1)
	{
		i = 0;
		if (pthread_create(&env->god, NULL, &fn_god, env) != 0)
			return (ft_error_exit(env, "thread create error\n"));
		while (i < env->philo_size)
		{
			if (pthread_create(&env->philo[i], NULL, &fn_thread, env) != 0)
				return (ft_error_exit(env, "thread create error\n"));
			i++;
		}
		if (pthread_join(env->god, NULL) != 0)
			return (ft_error_exit(env, "thread join : error\n"));
	}
	else
	{
		alone_philo(env);
		clean_out(env);
	}
	return (0);
}

int	main(int ac, char *av[])
{
	t_env	env;

	if (ac < 5 || ac > 6)
	{
		write(STDERR_FILENO, "Error : bad input\n", 18);
		return (2);
	}
	if (get_input(av, ac, &env) != 0)
		return (2);
	if (start_thread(&env) != 0)
		return (2);
	printf("%lu :: process exit\n", get_dif_time(env.base_time));
	return (0);
}
