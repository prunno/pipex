/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicli <vicli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:05:44 by vicli             #+#    #+#             */
/*   Updated: 2025/12/18 15:04:12 by vicli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *buf, int c, size_t n)
{
	size_t			i;
	unsigned char	*s;

	s = (unsigned char *)buf;
	i = 0;
	while (i < n)
	{
		s[i] = c;
		++i;
	}
	return (buf);
}
