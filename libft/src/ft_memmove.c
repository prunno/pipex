/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicli <vicli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:09:18 by vicli             #+#    #+#             */
/*   Updated: 2025/12/18 15:04:12 by vicli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, void *src, size_t n)
{
	char	*dsts;
	char	*srcs;

	if (dst == src)
		return (dst);
	if (dst < src)
		return (ft_memcpy(dst, src, n));
	dsts = (char *) dst;
	srcs = (char *) src;
	while (n)
	{
		--n;
		dsts[n] = srcs[n];
	}
	return (dst);
}
