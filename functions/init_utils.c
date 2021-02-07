/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 18:45:06 by alancel           #+#    #+#             */
/*   Updated: 2021/02/03 20:50:50 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub.h"

void	map_init(t_map *map)
{
	int		i;

	i = 0;
	map->x = 0;
	map->y = 0;
	map->north = 0;
	map->south = 0;
	map->west = 0;
	map->east = 0;
	map->s = 0;
	map->sx = 0;
	map->sy = 0;
	map->player = 0;
	while (i < 4)
		map->floor[i++] = 0;
	i = 0;
	while (i < 4)
		map->ceil[i++] = 0;
}

void	init_direction(t_all *all, int i, int j)
{
	if (all->map.mas_map[i][j] == 'S' && !(all->player.plane_x = 0))
	{
		all->player.plane_y = -0.66;
		all->player.dir_y = 0.0000001;
		all->player.dir_x = 1;
	}
	if (all->map.mas_map[i][j] == 'N' && !(all->player.plane_x = 0))
	{
		all->player.plane_y = 0.66;
		all->player.dir_y = -0.00001;
		all->player.dir_x = -1;
	}
	if (all->map.mas_map[i][j] == 'E' && (all->player.plane_x = -0.66))
	{
		all->player.plane_y = 0;
		all->player.dir_y = -1;
		all->player.dir_x = 0;
	}
	if (all->map.mas_map[i][j] == 'W' && (all->player.plane_x = 0.66))
	{
		all->player.plane_y = 0;
		all->player.dir_y = 1;
		all->player.dir_x = 0;
	}
	all->map.mas_map[i][j] = '0';
}
