/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 18:47:37 by alancel           #+#    #+#             */
/*   Updated: 2021/02/05 18:02:49 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub.h"

void	step_ray(t_all *all, t_ray *ray)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (all->player.x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - all->player.x) * ray->deltadist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (all->player.y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - all->player.y) * ray->deltadist_y;
	}
}

void	hit_ray(t_all *all, t_ray *ray)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (all->map.mas_map[ray->map_x][ray->map_y] == '1')
			ray->hit = 1;
	}
}

void	wall_ray(t_all *all, t_ray *ray)
{
	if (ray->side == 0)
		ray->walldist = (ray->map_x - all->player.x +
		(1 - ray->step_x) / 2) / ray->raydir_x;
	else
		ray->walldist = (ray->map_y - all->player.y +
		(1 - ray->step_y) / 2) / ray->raydir_y;
	ray->line_h = ray->walldist ? (int)(all->map.y /
	ray->walldist) : (int)(all->map.y);
	ray->start = -ray->line_h / 2 + all->map.y / 2;
	ray->start = ray->start < 0 ? 0 : ray->start;
	ray->end = ray->line_h / 2 + all->map.y / 2;
	ray->end = ray->end >= all->map.y ? all->map.y - 1 : ray->end;
	if (ray->side == 0)
		ray->wall_x = all->player.y + ray->walldist * ray->raydir_y;
	else
		ray->wall_x = all->player.x + ray->walldist * ray->raydir_x;
	ray->wall_x -= floor((ray->wall_x));
	ray->tex_x = (int)(ray->wall_x * (double)(all->image[0].image_width));
	if (ray->side == 0 && ray->raydir_x > 0)
		ray->tex_x = all->image[0].image_width - ray->tex_x - 1;
	if (ray->side == 1 && ray->raydir_y < 0)
		ray->tex_x = all->image[0].image_width - ray->tex_x - 1;
	ray->step = 1.0 * all->image[0].image_height / ray->line_h;
	ray->tex_pos = (ray->start - all->map.y /
	2 + ray->line_h / 2) * ray->step;
}

void	lining(t_all *all, t_ray *ray, int x)
{
	int	color;
	int	y;

	y = 0;
	while (y < all->map.y)
	{
		if (y < ray->end && y > ray->start)
		{
			ray->tex_y = (int)ray->tex_pos &
			(all->image[0].image_height - 1);
			ray->tex_pos += ray->step;
		}
		color = put_color(all, ray, y);
		my_mlx_pixel_put(&all->apparition, x, y++, color);
	}
	all->zbuff[x] = ray->walldist;
}

void	ray_tex(t_all *all, t_ray *ray)
{
	int		x;

	x = 0;
	while (x < all->map.x)
	{
		ray->camera = 2 * x / (double)(all->map.x) - 1;
		ray->raydir_x = all->player.dir_x + all->player.plane_x * ray->camera;
		ray->raydir_y = all->player.dir_y + all->player.plane_y * ray->camera;
		ray->map_x = (int)all->player.x;
		ray->map_y = (int)all->player.y;
		if (!ray->raydir_y)
			ray->deltadist_x = 0;
		else
			ray->deltadist_x = fabs(1 / ray->raydir_x);
		if (!ray->raydir_y)
			ray->deltadist_y = 0;
		else
			ray->deltadist_y = fabs(1 / ray->raydir_y);
		step_ray(all, ray);
		hit_ray(all, ray);
		wall_ray(all, ray);
		lining(all, ray, x);
		x++;
	}
}
