/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicli <vicli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:09:28 by vicli             #+#    #+#             */
/*   Updated: 2025/12/18 15:04:15 by vicli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	long	n;
	int		sign;

	n = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		++nptr;
	if (*nptr == '+')
		++nptr;
	else if (*nptr == '-')
	{
		sign = -1;
		++nptr;
	}
	while ('0' <= *nptr && *nptr <= '9')
	{
		n = 10 * n + (*nptr - '0');
		++nptr;
	}
	return (n * sign);
}

int64_t	ft_atol(const char *nptr)
{
	long	n;
	int		sign;

	n = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		++nptr;
	if (*nptr == '+')
		++nptr;
	else if (*nptr == '-')
	{
		sign = -1;
		++nptr;
	}
	while ('0' <= *nptr && *nptr <= '9')
	{
		n = 10 * n + (*nptr - '0');
		++nptr;
	}
	return (n * sign);
}
