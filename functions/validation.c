/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 18:50:25 by alancel           #+#    #+#             */
/*   Updated: 2021/02/05 18:01:38 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub.h"

static void		check_all_utils(t_map *map, int i, int j)
{
	if ((map->mas_map[i][j] == '0' || map->mas_map[i][j] == '2'
	|| ft_memchr("NSWE", map->mas_map[i][j], 4))
	&& map->mas_map[i - 1][j] != '0' && map->mas_map[i - 1][j] != '1'
	&& map->mas_map[i - 1][j] != 'N' && map->mas_map[i - 1][j] != 'S'
	&& map->mas_map[i - 1][j] != 'W' && map->mas_map[i - 1][j] != 'E'
	&& map->mas_map[i - 1][j] != '2')
		kick_error(2);
}

static void		check_all(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	while (map->mas_map[++i])
	{
		j = 0;
		while (map->mas_map[i][++j])
		{
			if ((map->mas_map[i][j] == '0' || map->mas_map[i][j] == '2')
			&& !map->mas_map[i - 1][j])
				kick_error(2);
			if ((map->mas_map[i][j] == '0' || map->mas_map[i][j] == '2')
			&& map->mas_map[i + 1][j] != '1' && map->mas_map[i + 1][j] != '0'
			&& map->mas_map[i + 1][j] != 'N' && map->mas_map[i + 1][j] != 'S'
			&& map->mas_map[i + 1][j] != 'W' && map->mas_map[i + 1][j] != 'E'
			&& map->mas_map[i + 1][j] != '2' && map->mas_map[i - 1][j] != '1')
				kick_error(2);
			check_all_utils(map, i, j);
		}
	}
}

void			check_first_last(char *str)
{
	int		j;
	char	*str1;

	j = 0;
	str1 = miss_spaces(str);
	while (str1[j])
	{
		while (str1[j] == ' ')
			j++;
		if (str1[j] == '1' && str1[j + 1]
		!= ' ' && str1[j + 1]
		!= '1' && str1[j + 1] != '\n' && str1[j + 1] != '\0')
			kick_error(2);
		j++;
	}
}

void			check_surround(t_map *map)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (map->mas_map[i][0] == '\0')
		i++;
	check_first_last(map->mas_map[i]);
	while (map->mas_map[++i])
	{
		str = miss_spaces(map->mas_map[i]);
		j = -1;
		while (str[++j])
		{
			if ((str[j] == '0' || str[j] == '2' || ft_memchr("NSEW",
			map->mas_map[i][j], 4)) && str[j + 1] != '1' && str[j + 1] != '0'
			&& str[j + 1] != 'N' && str[j + 1] != 'S' && str[j + 1] != 'W'
			&& str[j + 1] != 'E' && str[j + 1] != '2')
				kick_error(2);
		}
		if (map->mas_map[i][0] == '\0')
			kick_error(2);
	}
	check_first_last(map->mas_map[i - 1]);
	check_all(map);
}

void			check_valid(t_map *map)
{
	int i;
	int j;

	i = -1;
	check_surround(map);
	while (map->mas_map[++i])
	{
		j = -1;
		while (map->mas_map[i][++j])
		{
			if (map->mas_map[i][j] == 'N' || map->mas_map[i][j] == 'S'
			|| map->mas_map[i][j] == 'E' || map->mas_map[i][j] == 'W')
			{
				if (map->player)
					kick_error(2);
				map->player = map->mas_map[i][j];
			}
			if (!ft_memchr("012 NSEW", map->mas_map[i][j], 8))
				kick_error(2);
		}
	}
	if (!map->player)
		kick_error(2);
}
