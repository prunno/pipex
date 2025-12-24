/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicli <vicli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 11:01:30 by vicli             #+#    #+#             */
/*   Updated: 2025/12/24 11:01:30 by vicli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_parent(t_env *env, int fd_pipe[2], int i, pid_t pid)
{
	if (env->heredoc && i == 0)
		handle_parent_heredoc(env);
	env->children[i] = pid;
	close(env->fd_in);
	env->fd_in = fd_pipe[0];
	close(fd_pipe[1]);
}

static void	handle_child(t_env *env, int i, int fd_pipe_out)
{
	int	r;

	if (env->fd_in < 0)
		(free_env(*env), exit(1));
	if (env->heredoc_pipe[1] >= 0)
		close(env->heredoc_pipe[1]);
	if (env->commands[i][0] == NULL)
		(free_env(*env), error_not_found(NULL), exit(127));
	r = get_fullpath(env, env->commands[i][0]);
	if (r == 1)
	{
		if (access(env->commands[i][0], F_OK))
			(error_not_found(env->commands[i][0]), free_env(*env), exit(127));
		if (!access(env->commands[i][0], X_OK))
			exec_file(env, env->commands[i][0], env->commands[i], fd_pipe_out);
		perror(env->commands[i][0]);
		free_env(*env);
		exit(126);
	}
	else if (r == 0)
		exec_file(env, env->binfile_path, env->commands[i], fd_pipe_out);
	free_env(*env);
	exit(127);
}

void	exec_cmds(t_env *env)
{
	int		fd_pipe[2];
	int		i;
	pid_t	pid;

	i = 0;
	while (i < env->n_cmds - 1)
	{
		pipe(fd_pipe);
		pid = fork();
		if (pid < 0)
			return ;
		if (pid == 0)
			(close(fd_pipe[0]), handle_child(env, i, fd_pipe[1]));
		handle_parent(env, fd_pipe, i, pid);
		i++;
	}
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
		handle_child(env, i, env->fd_out);
	env->children[i] = pid;
	close(env->fd_in);
	close(env->fd_out);
	wait_all(env);
}

static void	default_pipex(t_env *env)
{
	env->heredoc_pipe[0] = -1;
	env->heredoc_pipe[1] = -1;
	if (access(env->file_in, R_OK))
		perror(env->file_in);
	env->fd_in = open(env->file_in, O_RDONLY);
	env->fd_out = open(env->file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	exec_cmds(env);
}

int	main(int argc, char *argv[], char **envp)
{
	t_env	env;

	if (argc < 5)
		return (1);
	if (parse_args(&env, argc - 1, &argv[1]))
		return (1);
	env.envp = envp;
	env.path = get_path(envp);
	env.binfile_path = (char *) malloc(BUFFER_SIZE + 1);
	if (env.binfile_path == NULL)
		return (free_commands(env.commands), 1);
	env.binfile_size = BUFFER_SIZE;
	env.children = (pid_t *) malloc(sizeof(pid_t) * env.n_cmds);
	if (env.children == NULL)
		return (free_env(env), 1);
	if (env.heredoc == NULL)
		default_pipex(&env);
	else
		heredoc_pipex(&env);
	free_env(env);
	return (get_exit_status(env));
}
