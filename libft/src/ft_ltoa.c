/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicli <vicli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:26:12 by vicli             #+#    #+#             */
/*   Updated: 2025/12/18 15:04:14 by vicli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digits_u(uint64_t n)
{
	size_t	counter;

	if (!n)
		return (1);
	counter = 0;
	while (n)
	{
		counter++;
		n /= 10;
	}
	return (counter);
}

static size_t	count_digits(int64_t n)
{
	size_t	counter;

	if (!n)
		return (1);
	counter = 0;
	while (n)
	{
		counter++;
		n /= 10;
	}
	return (counter);
}

char	*ft_lutoa(uint64_t n)
{
	char	*nptr;
	size_t	len;

	len = count_digits_u(n);
	nptr = (char *)malloc((len + 1) * sizeof(char));
	if (nptr == NULL)
		return (NULL);
	nptr[len] = 0;
	nptr[0] = '0';
	while (n)
	{
		nptr[len - 1] = n % 10 + '0';
		len--;
		n /= 10;
	}
	return (nptr);
}

char	*ft_ltoa(int64_t n)
{
	char	*nptr;
	size_t	len;

	len = count_digits(n);
	if (n < 0)
		len++;
	nptr = (char *)malloc((len + 1) * sizeof(char));
	if (nptr == NULL)
		return (NULL);
	nptr[len] = 0;
	nptr[0] = '0';
	if (n < 0)
	{
		nptr[0] = '-';
		n = -n;
	}
	while (n)
	{
		nptr[len - 1] = ft_absl(n % 10) + '0';
		len--;
		n /= 10;
	}
	return (nptr);
}
