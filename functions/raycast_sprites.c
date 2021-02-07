/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 18:48:51 by alancel           #+#    #+#             */
/*   Updated: 2021/02/05 18:06:55 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub.h"

void	put_sprt(t_all *all, t_ray_s *rsprt, int colors, int x)
{
	int		stripe;
	int		tex[2];
	int		y_d[2];

	stripe = rsprt->start_x - 1;
	while (++stripe < rsprt->end_x)
	{
		tex[0] = (int)(x * (stripe - (-rsprt->sprt_w / 2 +
		rsprt->scrn_x)) * all->image[4].image_width / rsprt->sprt_w) / x;
		if (rsprt->trans_y >= 0 && stripe >= 0 && stripe
		< all->map.x && rsprt->trans_y < all->zbuff[stripe] + 1)
		{
			y_d[0] = rsprt->start_y - 1;
			while (++y_d[0] < rsprt->end_y)
			{
				y_d[1] = (y_d[0]) * x - all->map.y * 128 + rsprt->sprt_h * 128;
				tex[1] = ((y_d[1] * all->image[4].image_height) /
				rsprt->sprt_h) / x;
				colors = all->image[4].direction[all->image[4].image_height
				* tex[1] + tex[0]];
				if (colors & 0x00FFFFFF)
					my_mlx_pixel_put(&all->apparition, stripe, y_d[0], colors);
			}
		}
	}
}

void	sprt_se(t_all *all, t_ray_s *rsprt)
{
	int	colors;

	rsprt->scrn_x = (int)((all->map.x / 2) *
	(1 + rsprt->trans_x / rsprt->trans_y));
	rsprt->sprt_h = abs((int)(all->map.y / rsprt->trans_y));
	colors = 0;
	rsprt->start_y = -rsprt->sprt_h / 2 + all->map.y / 2;
	if (rsprt->start_y < 0)
		rsprt->start_y = 0;
	rsprt->end_y = rsprt->sprt_h / 2 + all->map.y / 2;
	if (rsprt->end_y >= all->map.y)
		rsprt->end_y = all->map.y - 1;
	if (all->map.y - all->map.x > 500)
		rsprt->sprt_w = abs((int)(all->map.x / rsprt->trans_y));
	else
		rsprt->sprt_w = abs((int)(all->map.y / rsprt->trans_y));
	rsprt->start_x = -rsprt->sprt_w / 2 + rsprt->scrn_x;
	if (rsprt->start_x < 0)
		rsprt->start_x = 0;
	rsprt->end_x = rsprt->sprt_w / 2 + rsprt->scrn_x;
	if (rsprt->end_x >= all->map.x)
		rsprt->end_x = all->map.x - 1;
	put_sprt(all, rsprt, colors, 256);
}

void	sort_sprt(t_sprite *sprt, const int n)
{
	int			i;
	int			left;
	int			flag;
	t_sprite	buf;

	flag = 1;
	left = 0;
	while (flag)
	{
		flag = 0;
		i = n - 1;
		while (i > left)
		{
			if (sprt[i - 1].distance > sprt[i].distance)
			{
				buf = sprt[i];
				sprt[i] = sprt[i - 1];
				sprt[i - 1] = buf;
				flag = 1;
			}
			i--;
		}
		left++;
	}
}

int		ray_sprt(t_all *all)
{
	t_ray_s	rsprt;
	int		i;

	i = all->sprite_quantity;
	while (i--)
	{
		all->sprite[i].distance = ((all->player.x - all->sprite[i].sprite_x) *
		(all->player.x - all->sprite[i].sprite_x) + (all->player.y -
		all->sprite[i].sprite_y) * (all->player.y - all->sprite[i].sprite_y));
	}
	sort_sprt(all->sprite, all->sprite_quantity);
	i = all->sprite_quantity;
	while (i--)
	{
		rsprt.sprite_x = all->sprite[i].sprite_x - all->player.x;
		rsprt.sprite_y = all->sprite[i].sprite_y - all->player.y;
		rsprt.inv = 1.0 / (all->player.plane_x * all->player.dir_y
		- all->player.dir_x * all->player.plane_y);
		rsprt.trans_x = rsprt.inv * (all->player.dir_y * rsprt.sprite_x
		- all->player.dir_x * rsprt.sprite_y);
		rsprt.trans_y = rsprt.inv * (-all->player.plane_y * rsprt.sprite_x
		+ all->player.plane_x * rsprt.sprite_y);
		sprt_se(all, &rsprt);
	}
	return (0);
}
