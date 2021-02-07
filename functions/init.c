/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 18:44:32 by alancel           #+#    #+#             */
/*   Updated: 2021/02/05 18:01:01 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub.h"

void	init_image(t_all *all)
{
	all->apparition.image = mlx_new_image(all->mlx, all->map.x, all->map.y);
	all->image[0].image = mlx_xpm_file_to_image(all->mlx,
	all->map.west, &all->image[0].image_width, &all->image[0].image_height);
	all->image[1].image = mlx_xpm_file_to_image(all->mlx,
	all->map.north, &all->image[1].image_width, &all->image[1].image_height);
	all->image[2].image = mlx_xpm_file_to_image(all->mlx,
	all->map.south, &all->image[2].image_width, &all->image[2].image_height);
	all->image[3].image = mlx_xpm_file_to_image(all->mlx,
	all->map.east, &all->image[3].image_width, &all->image[3].image_height);
	all->image[4].image = mlx_xpm_file_to_image(all->mlx,
	all->map.s, &all->image[4].image_width, &all->image[4].image_height);
	if (!all->image[0].image || !all->image[1].image || !all->image[2].image ||
	!all->image[3].image || !all->image[4].image)
		kick_error(2);
}

void	init_address(t_all *all)
{
	all->apparition.address = mlx_get_data_addr(all->apparition.image,
	&all->apparition.bpp, &all->apparition.length, &all->apparition.endian);
	all->image[0].direction = (int*)mlx_get_data_addr(all->image[0].image,
	&all->image[0].bpp, &all->image[0].length, &all->image[0].endian);
	all->image[1].direction = (int*)mlx_get_data_addr(all->image[1].image,
	&all->image[1].bpp, &all->image[1].length, &all->image[1].endian);
	all->image[2].direction = (int*)mlx_get_data_addr(all->image[2].image,
	&all->image[2].bpp, &all->image[2].length, &all->image[2].endian);
	all->image[3].direction = (int*)mlx_get_data_addr(all->image[3].image,
	&all->image[3].bpp, &all->image[3].length, &all->image[3].endian);
	all->image[4].direction = (int*)mlx_get_data_addr(all->image[4].image,
	&all->image[4].bpp, &all->image[4].length, &all->image[4].endian);
}

void	init_all(t_all *all)
{
	int		i;
	int		j;

	i = 0;
	all->sprite_quantity = 0;
	while (all->map.mas_map[i])
	{
		j = 0;
		while (all->map.mas_map[i][j])
		{
			if ((ft_strchr("NSWE", all->map.mas_map[i][j])))
			{
				all->player.x = i + 0.5;
				all->player.y = j + 0.5;
				init_direction(all, i, j);
			}
			if (all->map.mas_map[i][j] == '2')
				all->sprite_quantity++;
			j++;
		}
		i++;
	}
	if (!(all->sprite = malloc(sizeof(t_sprite) * all->sprite_quantity)))
		kick_error(3);
}

void	init_sprite(t_all *all)
{
	int		i;
	int		j;
	int		sprite_quantity;

	i = 0;
	sprite_quantity = 0;
	while (all->map.mas_map[i])
	{
		j = 0;
		while (all->map.mas_map[i][j])
		{
			if (all->map.mas_map[i][j] == '2')
			{
				all->sprite[sprite_quantity].sprite_x = i + 0.5;
				all->sprite[sprite_quantity++].sprite_y = j + 0.5;
			}
			j++;
		}
		i++;
	}
}

t_all	init(t_map map)
{
	t_all	all;

	all.map = map;
	init_all(&all);
	all.mlx = mlx_init();
	check_scrsize(&all);
	all.win = mlx_new_window(all.mlx, all.map.x, all.map.y, "cub3D");
	init_image(&all);
	init_address(&all);
	all.map.floor1 = (all.map.floor[0] << 16) +
	(all.map.floor[1] << 8) + all.map.floor[2];
	all.map.ceil1 = (all.map.ceil[0] << 16) +
	(all.map.ceil[1] << 8) + all.map.ceil[2];
	all.player.mvleft = 0;
	all.player.mvright = 0;
	all.player.front = 0;
	all.player.back = 0;
	all.player.left = 0;
	all.player.right = 0;
	return (all);
}
