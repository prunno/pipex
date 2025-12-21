/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicli <vicli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:59:37 by vicli             #+#    #+#             */
/*   Updated: 2025/12/18 15:04:14 by vicli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_split(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		++i;
	}
	free(strs);
}

size_t	count_words(char const *s, char c)
{
	size_t	start;
	size_t	end;
	size_t	counter;

	counter = 0;
	start = 0;
	while (s[start])
	{
		while (s[start] && s[start] == c)
			++start;
		end = start;
		while (s[end] && s[end] != c)
			++end;
		if (start < end)
			++counter;
		start = end;
	}
	return (counter);
}

char	**ft_split_aux(char **strs, char const *s, char c)
{
	size_t	start;
	size_t	end;
	size_t	i;

	i = 0;
	start = 0;
	while (s[start])
	{
		while (s[start] && s[start] == c)
			++start;
		end = start;
		while (s[end] && s[end] != c)
			++end;
		if (start < end)
		{
			strs[i] = ft_substr(s, start, end - start);
			if (strs[i] == NULL)
				return (NULL);
			++i;
		}
		start = end;
	}
	strs[i] = NULL;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;

	if (s == NULL)
		return (NULL);
	strs = (char **) malloc((count_words(s, c) + 1) * sizeof(char *));
	if (strs == NULL)
		return (NULL);
	if (ft_split_aux(strs, s, c) == NULL)
	{
		free_split(strs);
		return (NULL);
	}
	return (strs);
}
