/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicli <vicli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:41:57 by vicli             #+#    #+#             */
/*   Updated: 2025/12/18 15:04:14 by vicli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	len_s1;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	join = (char *)malloc((len_s1 + ft_strlen(s2) + 1) * sizeof(char));
	if (join == NULL)
		return (NULL);
	ft_strcpy(join, (char *)s1);
	ft_strcpy(&join[len_s1], (char *)s2);
	return (join);
}
