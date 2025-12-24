/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicli <vicli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 11:01:28 by vicli             #+#    #+#             */
/*   Updated: 2025/12/24 11:01:28 by vicli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_exit_status(t_env env)
{
	if (WIFEXITED(env.exit_status))
		return (WEXITSTATUS(env.exit_status));
	return (127);
}

void	wait_all(t_env *env)
{
	int	i;

	// waitpid(env->children[env->n_cmds - 1], &env->exit_status, 0);
	i = 0;
	while (i < env->n_cmds)
	{
		waitpid(env->children[i], &env->exit_status, 0);
		i++;
	}
	i = 0;
	while (i < env->n_cmds)
	{
		while (!waitpid(-1, NULL, 0))
			;
		i++;
	}
}
