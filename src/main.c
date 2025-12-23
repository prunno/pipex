#include "pipex.h"
#include <stdlib.h>

int	get_exit_status(t_env env)
{
	if (WIFEXITED(env.exit_status))
		return (WEXITSTATUS(env.exit_status));
	return (127);
}

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
			return (free_commands(env->commands), 1);
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
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (envp[i]);
		i++;
	}
	return (NULL);
}

int	get_fullpath(t_env *env, char *command)
{
	int			i;
	int			j;
	const int	cmd_len = ft_strlen(command);

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

void	wait_all(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->n_cmds)
	{
		waitpid(env->children[i], &env->exit_status, 0);
		i++;
	}
}

int	parse_limiter(char *limiter, char *buf)
{
	int	i;
	int	j;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		while (i < BUFFER_SIZE && buf[i] == '\n')
			i++;
		j = i;
		while (i < BUFFER_SIZE && buf[i] != '\n')
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
	l_return = parse_limiter(env->heredoc, line);
	while (!l_return)
	{
		line[read_return] = '\0';
		write(env->heredoc_pipe[1], line, read_return);
		write(STDOUT_FILENO, "heredoc> ", ft_strlen("heredoc> "));
		read_return = read(STDIN_FILENO, line, BUFFER_SIZE);
		l_return = parse_limiter(env->heredoc, line);
	}
	write(env->heredoc_pipe[1], line, l_return - ft_strlen(env->heredoc));
	close(env->heredoc_pipe[1]);
	env->heredoc_pipe[1] = -1;
}

void	handle_parent(t_env *env, int fd_pipe[2], int i, pid_t pid)
{
	if (env->heredoc && i == 0)
		handle_parent_heredoc(env);
	env->children[i] = pid;
	close(env->fd_in);
	env->fd_in = fd_pipe[0];
	close(fd_pipe[1]);
}

void	exec_file(t_env *env, char *cmd, char **argv, int fd_pipe_out)
{
	int	dummy[2];
	
	close(STDOUT_FILENO);
	if (fd_pipe_out >= 0)
	{
		dup2(fd_pipe_out, STDOUT_FILENO);
		close(fd_pipe_out);
	}
	else
	{
		pipe(dummy);
		close(dummy[0]);
		dup2(dummy[1], STDOUT_FILENO);
		close(dummy[1]);
	}
	close(STDIN_FILENO);
	dup2(env->fd_in, STDIN_FILENO);
	close(env->fd_in);
	execve(cmd, argv, env->envp);
}

void	handle_child(t_env *env, int i, int fd_pipe_out)
{
	int	r;

	if (env->fd_in < 0)
		free_env(*env), exit(1);
	if (env->heredoc_pipe[1] >= 0)
		close(env->heredoc_pipe[1]);
	if (env->commands[i][0] == NULL)
		free_env(*env), exit(127);
	r = get_fullpath(env, env->commands[i][0]);
	if (r == 1)
	{
		if (!access(env->commands[i][0], X_OK))
			exec_file(env, env->commands[i][0], env->commands[i], fd_pipe_out);
		perror(env->commands[i][0]);
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
			handle_child(env, i, fd_pipe[1]);
		handle_parent(env, fd_pipe, i, pid);
		i++;
	}
	dup2(env->fd_out, STDOUT_FILENO);
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

void	default_pipex(t_env *env)
{
	env->heredoc_pipe[0] = -1;
	env->heredoc_pipe[1] = -1;
	if (access(env->file_in, R_OK))
		perror(env->file_in);
	env->fd_in = open(env->file_in, O_RDONLY);
	if (!access(env->file_out, F_OK) && access(env->file_out, W_OK))
		perror(env->file_out);
	env->fd_out = open(env->file_out, OPEN_DEFAULT, 0644);
	exec_cmds(env);
}

void	heredoc_pipex(t_env *env)
{
	pipe(env->heredoc_pipe);
	env->fd_in = env->heredoc_pipe[0];
	if (!access(env->file_out, F_OK) && access(env->file_out, W_OK))
		perror(env->file_out);
	env->fd_out = open(env->file_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	exec_cmds(env);
}

int	main(int argc, char *argv[], char **envp)
{
	t_env	env;

	if (argc < 5)
		return (0);
	if (parse_args(&env, argc - 1, &argv[1]))
		return (1);
	env.envp = envp;
	env.path = get_path(envp);
	env.binfile_path = (char *) malloc(BUFFER_SIZE + 1);
	env.binfile_size = BUFFER_SIZE;
	env.children = (pid_t *) malloc(sizeof(pid_t) * env.n_cmds);
	if (env.binfile_path)
	{
		if (env.heredoc == NULL)
			default_pipex(&env);
		else
			heredoc_pipex(&env);
	}
	free_env(env);
	if (!access(env.file_out, F_OK) && access(env.file_out, W_OK))
		return (1);
	return (get_exit_status(env));
}
