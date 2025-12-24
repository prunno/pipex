/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicli <vicli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 11:01:28 by vicli             #+#    #+#             */
/*   Updated: 2025/12/24 11:01:28 by vicli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_commands(char ***commands)
{
	int	i;

	i = 0;
	while (commands[i] != NULL)
	{
		free_split(commands[i]);
		i++;
	}
	free(commands);
}

void	free_env(t_env env)
{
	free_commands(env.commands);
	free(env.children);
	free(env.binfile_path);
}
