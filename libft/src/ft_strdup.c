/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicli <vicli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:09:42 by vicli             #+#    #+#             */
/*   Updated: 2025/12/18 15:04:16 by vicli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*dst;
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	dst = (char *)malloc(sizeof(char) * (src_len + 1));
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (i < src_len)
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = '\0';
	return (dst);
}
