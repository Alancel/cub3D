/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:14:58 by alancel           #+#    #+#             */
/*   Updated: 2021/02/02 18:54:45 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int					ft_check_endl(char *str)
{
	int				i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char				*ft_remainder_empty(char *remainder)
{
	char			*str;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	if (!remainder)
		return (0);
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (!remainder[i])
	{
		free(remainder);
		return (0);
	}
	if (!(str = malloc(sizeof(char) * ((ft_strlen(remainder) - i) + 1))))
		return (0);
	i++;
	while (remainder[i])
		str[j++] = remainder[i++];
	str[j] = '\0';
	free(remainder);
	return (str);
}

char				*ft_write_line(char *str)
{
	int				i;
	char			*tmp;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (!(tmp = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int					get_next_line(int fd, char **line)
{
	char			*buff;
	static char		*remainder;
	int				byte_reader;

	byte_reader = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (!ft_check_endl(remainder) && byte_reader != 0)
	{
		if ((byte_reader = read(fd, buff, BUFFER_SIZE)) == -1)
		{
			free(buff);
			return (-1);
		}
		buff[byte_reader] = '\0';
		remainder = ft_str_join(remainder, buff);
	}
	free(buff);
	*line = ft_write_line(remainder);
	remainder = ft_remainder_empty(remainder);
	if (byte_reader == 0)
		return (0);
	return (1);
}
