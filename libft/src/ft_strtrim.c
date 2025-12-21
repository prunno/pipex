/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicli <vicli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:57:35 by vicli             #+#    #+#             */
/*   Updated: 2025/12/18 15:04:13 by vicli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_charset(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *str, char const *set)
{
	char	*new;
	size_t	start;
	size_t	end;

	if (str == NULL || set == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(str);
	while (check_charset(str[start], (char *)set))
		start++;
	while (end > 0 && check_charset(str[end - 1], (char *)set))
		end--;
	if (end <= start)
	{
		new = (char *) malloc(sizeof(char));
		if (new == NULL)
			return (NULL);
		new[0] = '\0';
		return (new);
	}
	return (ft_substr(str, start, end - start));
}
