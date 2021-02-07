/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 18:42:33 by alancel           #+#    #+#             */
/*   Updated: 2021/02/02 23:10:46 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub.h"

void	pars_flcl(char *str, int *red, int *green, int *blue)
{
	str = miss_spaces(str);
	while (ft_isdigit(*str))
		*red = *red * 10 + (*(str++) - '0');
	str = miss_spaces(str);
	if (*(str++) != ',')
		kick_error(2);
	str = miss_spaces(str);
	while (ft_isdigit(*str))
		*green = *green * 10 + (*(str++) - '0');
	str = miss_spaces(str);
	if (*(str++) != ',')
		kick_error(2);
	str = miss_spaces(str);
	while (ft_isdigit(*str))
		*blue = *blue * 10 + (*(str++) - '0');
	str = miss_spaces(str);
	if (*str != '\0')
		kick_error(2);
	if (*red < 0 || *red > 255 || *green < 0 ||
	*green > 255 || *blue < 0 || *blue > 255)
		kick_error(2);
}

char	*miss_spaces(char *str)
{
	while (*str == ' ')
		str++;
	return (str);
}

char	*put_line(char *line)
{
	char	*b_line;
	char	*strt;
	char	*end;
	char	*tmp;

	if (!(b_line = (char*)malloc(ft_strlen(line))))
		kick_error(3);
	line = miss_spaces(line);
	strt = line;
	while (*(line + 1))
		line++;
	while (*line == ' ' && line >= strt)
		line--;
	end = line;
	*(++end) = '\0';
	tmp = b_line;
	while (strt <= end)
		*(tmp++) = *(strt++);
	return (b_line);
}
