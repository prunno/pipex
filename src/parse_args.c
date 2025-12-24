/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicli <vicli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 11:01:30 by vicli             #+#    #+#             */
/*   Updated: 2025/12/24 11:01:30 by vicli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
