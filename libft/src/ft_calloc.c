/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicli <vicli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:13:57 by vicli             #+#    #+#             */
/*   Updated: 2025/12/18 15:04:16 by vicli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t capacity, size_t n_bytes)
{
	void	*buf;
	size_t	total_bytes;

	if (!capacity || !n_bytes)
		return (malloc(0));
	if (SIZE_MAX / n_bytes < capacity)
		return (NULL);
	total_bytes = capacity * n_bytes;
	buf = malloc(total_bytes);
	if (buf == NULL)
		return (NULL);
	return (ft_memset(buf, 0, total_bytes));
}
