/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicli <vicli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:09:12 by vicli             #+#    #+#             */
/*   Updated: 2025/12/18 15:04:13 by vicli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dsts;
	char	*srcs;

	if (dst == NULL && src == NULL)
		return (NULL);
	dsts = (char *) dst;
	srcs = (char *) src;
	i = 0;
	while (i < n)
	{
		dsts[i] = srcs[i];
		++i;
	}
	return (dst);
}
