/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 21:07:44 by alancel           #+#    #+#             */
/*   Updated: 2020/11/04 16:52:01 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int					ft_length(int n)
{
	int						i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static	char				ft_putnbr(int n)
{
	return ((n % 10) + '0');
}

static	void				*ft_check(int n)
{
	unsigned int			tmp;
	char					*str;

	tmp = n;
	if (n < 0)
		tmp = -n;
	if (tmp >= 2147483648)
	{
		str = (char*)ft_calloc(12, sizeof(char));
		if (!str)
			return (NULL);
		ft_strlcpy(str, "-2147483648", 12);
		return (str);
	}
	return (NULL);
}

char						*ft_itoa(int n)
{
	char					*str;
	int						length;

	length = ft_length(n) - 1;
	if ((str = ft_check(n)))
		return (str);
	if (!(str = (char*)ft_calloc(length + 2, sizeof(char))))
		return (NULL);
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		n = n * (-1);
	}
	while (n != 0)
	{
		str[length--] = ft_putnbr(n);
		n = n / 10;
	}
	return (str);
}
