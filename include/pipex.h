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

# define BUFFER_SIZE 4096 * 16
# define OPEN_DEFAULT O_WRONLY | O_CREAT | O_TRUNC

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

#endif
