/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicli <vicli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:19:13 by vicli             #+#    #+#             */
/*   Updated: 2025/12/18 15:04:13 by vicli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t n)
{
	size_t	dst_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (!n)
		return (src_len);
	dst_len = ft_strlen(dst);
	if (dst_len >= n)
		return (n + src_len);
	return (ft_strlcpy(&dst[dst_len], src, n - dst_len) + dst_len);
}
