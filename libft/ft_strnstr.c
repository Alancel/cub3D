/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:40:00 by alancel           #+#    #+#             */
/*   Updated: 2020/10/30 20:42:33 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*str2)
		return ((char *)str1);
	while (str1[i] != '\0' && i < len)
	{
		if (str1[i] == str2[0])
		{
			while (str2[j] != '\0' && str1[i + j] == str2[j] && i + j < len)
			{
				if (str2[j + 1] == '\0')
					return ((char *)&str1[i]);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
