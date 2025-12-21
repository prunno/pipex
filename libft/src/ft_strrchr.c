/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicli <vicli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:18:30 by vicli             #+#    #+#             */
/*   Updated: 2025/12/18 15:04:12 by vicli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c_int)
{
	int		i;
	char	c;

	c = (char) c_int;
	if (!c)
		return ((char *)s + ft_strlen(s));
	i = ft_strlen(s) - 1;
	while (i >= 0)
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		--i;
	}
	return (NULL);
}
