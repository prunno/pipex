/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicli <vicli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 11:00:52 by vicli             #+#    #+#             */
/*   Updated: 2025/12/24 11:01:31 by vicli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_fullpath(t_env *env, char *cmd)
{
	int			i;
	int			j;

	i = 0;
	while (env->path[i])
	{
		j = i;
		while (env->path[j] && env->path[j] != ':')
			j++;
		if ((size_t)env->binfile_size <= j - i + ft_strlen(cmd) + 2)
		{
			env->binfile_size = (j - i + ft_strlen(cmd) + 2) * 2;
			free(env->binfile_path);
			env->binfile_path = (char *) malloc(env->binfile_size + 1);
			if (env->binfile_path == NULL)
				return (-1);
		}
		ft_memcpy(env->binfile_path, &env->path[i], j - i);
		ft_memcpy(&env->binfile_path[j - i], "/", 1);
		ft_strlcpy(&env->binfile_path[j - i + 1], cmd, ft_strlen(cmd) + 1);
		if (!access(env->binfile_path, X_OK))
			return (0);
		i = j + 1;
	}
	return (1);
}

void	exec_file(t_env *env, char *cmd, char **argv, int fd_pipe_out)
{
	if (fd_pipe_out < 0 && access(env->file_out, W_OK))
	{
		perror(env->file_out);
		free_env(*env);
		exit(1);
	}
	close(STDOUT_FILENO);
	dup2(fd_pipe_out, STDOUT_FILENO);
	close(fd_pipe_out);
	close(STDIN_FILENO);
	dup2(env->fd_in, STDIN_FILENO);
	close(env->fd_in);
	execve(cmd, argv, env->envp);
	perror(cmd);
	free_env(*env);
	exit(126);
}
