/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicli <vicli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 11:02:17 by vicli             #+#    #+#             */
/*   Updated: 2025/12/24 11:02:17 by vicli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

# include "libft.h"

# define BUFFER_SIZE 4096

typedef struct s_env
{
	int		exit_status;
	char	*file_in;
	char	*file_out;
	int		fd_in;
	int		fd_out;
	char	***commands;
	int		n_cmds;
	char	*binfile_path;
	int		binfile_size;
	char	*heredoc;
	int		heredoc_pipe[2];
	char	*path;
	pid_t	*children;
	char	**envp;
}	t_env;

void	free_commands(char ***commands);
void	free_env(t_env env);

char	*get_path(char **envp);
int		parse_args(t_env *env, int argc, char *argv[]);

int		parse_limiter(char *limiter, char *buf, int size);
void	handle_parent_heredoc(t_env *env);
void	heredoc_pipex(t_env *env);

int		get_fullpath(t_env *env, char *command);
void	exec_file(t_env *env, char *cmd, char **argv, int fd_pipe_out);

int		get_exit_status(t_env env);
void	wait_all(t_env *env);

void	exec_cmds(t_env *env);

#endif
