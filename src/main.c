#include "pipex.h"

void	write_output(int fd_out, int fd_in)
{
	char	buf[BUFFER_SIZE];
	int		read_return;

	read_return = read(fd_in, buf, BUFFER_SIZE);
	while (read_return > 0)
	{
		write(fd_out, buf, read_return);
		read_return = read(fd_in, buf, BUFFER_SIZE);
	}
}

void	free_env(t_env env)
{

	int	i;

	i = 0;
	while (env.commands[i] != NULL)
	{
		free_split(env.commands[i]);
		i++;
	}
	free(env.commands);
	free(env.binfile_path);
}

int	parse_args(t_env *env, int argc, char *argv[])
{
	int		i;

	i = 1;
	env->heredoc = NULL;
	if (!ft_strcmp(argv[0], "here_doc"))
	{
		env->heredoc = argv[1];
		argc--;
		argv++;
	}
	env->commands = (char ***) malloc(sizeof(char **) * (argc - 1));
	if (env->commands == NULL)
		return (1);
	env->commands[argc - 2] = NULL;
	env->n_cmds = argc - 2;
	env->file_in = argv[0];
	env->file_out = argv[argc - 1];
	while (i < argc - 1)
	{
		env->commands[i - 1] = ft_split(argv[i], ' ');
		if (env->commands[i - 1] == NULL)
			return (free_env(*env), 1);
		i++;
	}
	return (0);
}

char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH", 4))
			return (envp[i]);
		i++;
	}
	return (NULL);
}

int	get_fullpath(t_env *env, char *command)
{
	int	i;
	int	j;
	int	cmd_len = ft_strlen(command);

	i = 0;
	while (env->path[i])
	{
		j = i;
		while (env->path[j] && env->path[j] != ':')
			j++;
		if (env->binfile_size <= j - i + cmd_len + 2)
		{
			env->binfile_size = (j - i + cmd_len + 2) * 2;
			free(env->binfile_path);
			env->binfile_path = (char *) malloc(env->binfile_size + 1);
			if (env->binfile_path == NULL)
				return (-1);
		}
		ft_memcpy(env->binfile_path, &env->path[i], j - i);
		ft_memcpy(&env->binfile_path[j - i], "/", 1);
		ft_strlcpy(&env->binfile_path[j - i + 1], command, cmd_len + 1);
		if (!access(env->binfile_path, X_OK))
			return (0);
		i = j + 1;
	}
	return (1);
}

void	close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	handle_parent_heredoc(t_env *env, int fd_pipe_in[2], int fd_pipe_out[2])
{
	int		read_return;
	size_t	limiter_len;
	char	line[BUFFER_SIZE + 1];

	limiter_len = ft_strlen(env->heredoc);
	close(fd_pipe_out[1]);
	close(fd_pipe_in[0]);
	write(STDOUT_FILENO, "heredoc> ", ft_strlen("heredoc> "));
	read_return = read(env->fd_in, line, BUFFER_SIZE);
	while (read_return > 0)
	{
		line[read_return] = '\0';
		if (ft_strlen(line) == limiter_len + 1
			&& !ft_strncmp(line, env->heredoc, limiter_len))
			break ;
		write(fd_pipe_in[1], line, read_return);
		write(STDOUT_FILENO, "heredoc> ", ft_strlen("heredoc> "));
		read_return = read(env->fd_in, line, BUFFER_SIZE);
	}
	close(fd_pipe_in[1]);
	wait(NULL);
}

void	handle_parent_default(t_env *env, int fd_pipe_in[2], int fd_pipe_out[2])
{
	int		read_return;
	char	line[BUFFER_SIZE];

	close(fd_pipe_out[1]);
	close(fd_pipe_in[0]);
	read_return = read(env->fd_in, line, BUFFER_SIZE);
	while (read_return > 0)
	{
		write(fd_pipe_in[1], line, read_return);
		read_return = read(env->fd_in, line, BUFFER_SIZE);
	}
	close(fd_pipe_in[1]);
	wait(NULL);
}

void	handle_parent(t_env *env, int fd_pipe_in[2], int fd_pipe_out[2], int i)
{
	if (env->heredoc && i == 1)
		handle_parent_heredoc(env, fd_pipe_in, fd_pipe_out);
	else
		handle_parent_default(env, fd_pipe_in, fd_pipe_out);
}

void	exec_file(int fd_pipe_in[2], int fd_pipe_out[2], char *cmd, char **argv)
{
	close(STDIN_FILENO);
	dup2(fd_pipe_in[0], STDIN_FILENO);
	close(STDOUT_FILENO);
	dup2(fd_pipe_out[1], STDOUT_FILENO);
	close(fd_pipe_in[1]);
	close(fd_pipe_in[0]);
	close(fd_pipe_out[0]);
	execve(cmd, argv, NULL);
}

void	handle_child(t_env *env, int fd_pipe_in[2], int fd_pipe_out[2], int i)
{
	int	r;
	
	r = get_fullpath(env, env->commands[i][0]);
	if (r == 1)
	{
		if (!access(env->commands[i][0], X_OK))
			exec_file(fd_pipe_in, fd_pipe_out, env->commands[i][0], env->commands[i]);
		perror(env->commands[i][0]);
	}
	else if (r == 0)
		exec_file(fd_pipe_in, fd_pipe_out, env->binfile_path, env->commands[i]);
	exit(EXIT_FAILURE);
}

void	exec_cmds(t_env *env)
{
	int		fd_pipe_in[2];
	int		fd_pipe_out[2];
	int		i;
	pid_t	pid;

	i = 1;
	while (i < env->n_cmds)
	{
		pipe(fd_pipe_out);
		pipe(fd_pipe_in);
		pid = fork();
		if (pid < 0)
			return (close_pipe(fd_pipe_in));
		if (pid == 0)
			handle_child(env, fd_pipe_in, fd_pipe_out, i);
		else
			handle_parent(env, fd_pipe_in, fd_pipe_out, i);
		close(env->fd_in);
		env->fd_in = fd_pipe_out[0];
		i++;
	}
}

void	default_pipex(t_env *env)
{
	env->fd_in = open(env->file_in, O_RDONLY);
	if (env->fd_in < 0)
	{
		free_env(*env);
		exit(EXIT_FAILURE);
	}
	env->fd_out = open(env->file_out, OPEN_DEFAULT, 0644);
	if (env->fd_out < 0)
	{
		close(env->fd_in);
		free_env(*env);
		exit(EXIT_FAILURE);
	}
	exec_cmds(env);
	if (env->fd_in > 0)
		write_output(env->fd_out, env->fd_in);
	close(env->fd_out);
	close(env->fd_in);
}

void	heredoc_pipex(t_env *env)
{
	env->fd_in = STDIN_FILENO;
	env->fd_out = open(env->file_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (env->fd_out < 0)
	{
		close(env->fd_in);
		free_env(*env);
		exit(EXIT_FAILURE);
	}
	exec_cmds(env);
	if (env->fd_in > 0)
		write_output(env->fd_out, env->fd_in);
	close(env->fd_out);
	close(env->fd_in);
}

int	main(int argc, char *argv[], char **envp)
{
	t_env	env;

	if (argc < 5)
		return (0);
	if (parse_args(&env, argc - 1, &argv[1]))
		return (1);
	env.path = get_path(envp);
	env.binfile_path = (char *) malloc(BUFFER_SIZE + 1);
	env.binfile_size = BUFFER_SIZE;
	if (env.binfile_path)
	{
		if (env.heredoc == NULL)
			default_pipex(&env);
		else
			heredoc_pipex(&env);
	}
	free_env(env);
}
