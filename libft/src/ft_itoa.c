/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicli <vicli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:26:12 by vicli             #+#    #+#             */
/*   Updated: 2025/12/18 15:04:15 by vicli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_digits(int32_t n)
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

char	*ft_utoa(uint32_t n)
{
	char	*nptr;
	size_t	len;

	len = count_digits(n);
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

char	*ft_itoa(int32_t n)
{
	int64_t	nlong;
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
	nlong = (int64_t)n;
	if (nlong < 0)
	{
		nptr[0] = '-';
		nlong = -nlong;
	}
	while (nlong)
	{
		nptr[len - 1] = nlong % 10 + '0';
		len--;
		nlong /= 10;
	}
	return (nptr);
}
