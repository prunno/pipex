/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicli <vicli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 11:01:29 by vicli             #+#    #+#             */
/*   Updated: 2025/12/24 11:01:29 by vicli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	parse_limiter(char *limiter, char *buf, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		while (i < size && buf[i] == '\n')
			i++;
		j = i;
		while (i < size && buf[i] != '\n')
			i++;
		if (j != i && !ft_strncmp(limiter, &buf[j], i - j))
			return (i);
	}
	return (0);
}

void	handle_parent_heredoc(t_env *env)
{
	int		read_return;
	int		l_return;
	char	line[BUFFER_SIZE + 1];

	close(env->heredoc_pipe[0]);
	write(STDOUT_FILENO, "heredoc> ", ft_strlen("heredoc> "));
	read_return = read(STDIN_FILENO, line, BUFFER_SIZE);
	l_return = parse_limiter(env->heredoc, line, read_return);
	while (!l_return)
	{
		line[read_return] = '\0';
		write(env->heredoc_pipe[1], line, read_return);
		write(STDOUT_FILENO, "heredoc> ", ft_strlen("heredoc> "));
		read_return = read(STDIN_FILENO, line, BUFFER_SIZE);
		l_return = parse_limiter(env->heredoc, line, read_return);
	}
	write(env->heredoc_pipe[1], line, l_return - ft_strlen(env->heredoc));
	close(env->heredoc_pipe[1]);
	env->heredoc_pipe[1] = -1;
}

void	heredoc_pipex(t_env *env)
{
	pipe(env->heredoc_pipe);
	env->fd_in = env->heredoc_pipe[0];
	env->fd_out = open(env->file_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	exec_cmds(env);
}
