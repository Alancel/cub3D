/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:17:03 by alancel           #+#    #+#             */
/*   Updated: 2020/11/04 18:21:29 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_wlength(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

size_t	ft_word_amount(char const *s, char c)
{
	size_t amount;
	size_t split;

	amount = 0;
	split = 0;
	while (*s)
	{
		if (*s && split == 0 && *s != c)
		{
			amount++;
			split = 1;
		}
		else if (split == 1 && *s == c)
			split = 0;
		s++;
	}
	return (amount);
}

char	*ft_word_insert(char const *s, char c)
{
	size_t	i;
	char	*str;

	if (!(str = ft_calloc(ft_wlength(s, c) + 1, sizeof(char))))
		return (NULL);
	i = 0;
	while (*s && *s != c)
		str[i++] = *s++;
	str[i] = '\0';
	return (str);
}

void	ft_free(char **str, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
		free(str[i]);
	free(str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	i;

	if (!s || !(str = ft_calloc(ft_word_amount(s, c) + 1, sizeof(char **))))
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		if (*s && *s != c)
		{
			if (!(str[i++] = ft_word_insert(s, c)))
			{
				ft_free(str, ft_word_amount(s, c));
				return (NULL);
			}
			s += ft_wlength(s, c);
		}
	}
	str[i] = NULL;
	return (str);
}
