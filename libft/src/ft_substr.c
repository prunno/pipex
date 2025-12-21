/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicli <vicli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:54:28 by vicli             #+#    #+#             */
/*   Updated: 2025/12/18 15:04:16 by vicli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	len_s;
	char	*sub;

	if (s == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	sub = (char *)malloc(ft_minu64(len, ft_maxu64(len_s, start) - start) + 1);
	if (sub == NULL)
		return (NULL);
	i = 0;
	while (i + start < len_s && i < len)
	{
		sub[i] = s[start + i];
		++i;
	}
	sub[i] = '\0';
	return (sub);
}
