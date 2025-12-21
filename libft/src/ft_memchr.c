/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicli <vicli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:08:50 by vicli             #+#    #+#             */
/*   Updated: 2025/12/18 15:04:12 by vicli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *p, int c_int, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	c;

	s = (unsigned char *) p;
	c = (unsigned char) c_int;
	i = 0;
	while (i < n)
	{
		if (s[i] == c)
			return (p + i);
		++i;
	}
	return (NULL);
}
