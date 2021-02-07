/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 20:54:40 by alancel           #+#    #+#             */
/*   Updated: 2020/11/01 19:14:30 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_trim(char c, char const *set)
{
	size_t	i;

	i = -1;
	while (set[++i])
		if (set[i] == c)
			return (1);
	return (0);
}

int		ft_size(char const *s1, char const *set)
{
	size_t		i;
	size_t		size;

	i = 0;
	size = ft_strlen(s1);
	while (ft_trim(s1[size - i - 1], set))
		i++;
	return (size - i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	size;
	char	*str;

	i = 0;
	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	while (ft_trim(s1[i], set))
		i++;
	if (i == (size_t)ft_strlen(s1))
		return (ft_strdup(""));
	size = ft_size(s1 + i, set) + 1;
	if (!(str = (char *)malloc((size) * sizeof(char))))
		return (NULL);
	ft_strlcpy(str, s1 + i, size);
	return (str);
}
