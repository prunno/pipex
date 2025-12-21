#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "libft.h"

# define BUFFER_SIZE 4096

typedef struct s_env
{
	char	*file_in;
	char	*file_out;
	int		fd_in;
	int		fd_out;
	char	***commands;
	int		n_cmds;
	char	*binfile_path;
	int		binfile_size;
	int		heredoc;
	char	*path;
}	t_env;

#endif
