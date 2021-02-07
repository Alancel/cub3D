/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:56:22 by alancel           #+#    #+#             */
/*   Updated: 2020/10/30 20:30:37 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int sym)
{
	while (*str)
	{
		if (*str++ == (char)sym)
			return ((char *)str - 1);
	}
	if (sym == '\0')
		return ((char *)str);
	return (NULL);
}
