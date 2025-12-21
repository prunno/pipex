/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicli <vicli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:18:35 by vicli             #+#    #+#             */
/*   Updated: 2025/12/18 15:04:15 by vicli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

uint64_t	ft_minu64(uint64_t a, uint64_t b)
{
	if (a < b)
		return (a);
	return (b);
}

int64_t	ft_mini64(int64_t a, int64_t b)
{
	if (a < b)
		return (a);
	return (b);
}

uint32_t	ft_minu32(uint32_t a, uint32_t b)
{
	if (a < b)
		return (a);
	return (b);
}

int32_t	ft_mini32(int32_t a, int32_t b)
{
	if (a < b)
		return (a);
	return (b);
}
