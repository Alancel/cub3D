/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 20:39:12 by alancel           #+#    #+#             */
/*   Updated: 2020/10/30 20:33:51 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	size_t	i;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	if (!(str = malloc((ft_strlen(s1) + ft_strlen(s2) * sizeof(char) + 1))))
		return (NULL);
	size = ft_strlen(s1);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	i = -1;
	while (s2[++i])
		str[i + size] = s2[i];
	str[i + size] = '\0';
	return (str);
}
