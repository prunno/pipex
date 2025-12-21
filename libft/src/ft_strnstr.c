/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicli <vicli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:34:20 by vicli             #+#    #+#             */
/*   Updated: 2025/12/18 15:04:15 by vicli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *haystack, char *needle, size_t n)
{
	size_t	i;
	size_t	len_needle;

	if (needle[0] == '\0')
		return (haystack);
	if (n == 0)
		return (NULL);
	len_needle = ft_strlen(needle);
	i = 0;
	while (haystack[i] && i + len_needle <= n)
	{
		if (!ft_strncmp(&haystack[i], needle, len_needle))
			return (&haystack[i]);
		++i;
	}
	return (NULL);
}

/*
char	*ft_strnstr(char *haystack, char *needle, size_t n) {
	size_t i;
	size_t j;

	i = 0;
	while (haystack[i] && i < n) {
		j = 0;
		while (haystack[i + j] == needle[j] && needle[j] && i + j < n) {
			j++;
		}
		if (needle[j] == '\0') {
			return (&haystack[i]);
		}
		++i;
	}
	return (NULL);
}
*/
