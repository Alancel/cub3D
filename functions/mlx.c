/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 18:45:52 by alancel           #+#    #+#             */
/*   Updated: 2021/02/07 16:19:36 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub.h"

void	run_mlx(t_all *all)
{
	int x;

	print_picture(all);
	mlx_loop_hook(all->mlx, print_picture, all);
	mlx_hook(all->win, 2, (1L << 0), key_press, all);
	mlx_hook(all->win, 17, 0, kick_error, &x);
	mlx_hook(all->win, 3, (1L << 1), key_unpress, all);
	mlx_loop(all->mlx);
}

int		put_color(t_all *all, t_ray *ray, int y)
{
	int	color;

	color = 0;
	if (!ray->side && ray->raydir_x < 0 &&
	y < ray->end && y > ray->start)
		color = all->image[1].direction[all->image[1].image_height
		* ray->tex_y + ray->tex_x];
	else if (!ray->side && ray->raydir_x > 0 &&
	y < ray->end && y > ray->start)
		color = all->image[2].direction[all->image[2].image_height
		* ray->tex_y + ray->tex_x];
	else if (ray->side && ray->raydir_y < 0 &&
	y < ray->end && y > ray->start)
		color = all->image[0].direction[all->image[0].image_height
		* ray->tex_y + ray->tex_x];
	else if (ray->side && ray->raydir_y > 0 &&
	y < ray->end && y > ray->start)
		color = all->image[3].direction[all->image[3].image_height
		* ray->tex_y + ray->tex_x];
	else if (y < ray->start)
		color = all->map.floor1;
	else if (y > ray->end)
		color = all->map.ceil1;
	return (color);
}

void	my_mlx_pixel_put(t_evidence *data, int x, int y, int color)
{
	char	*dst;

	dst = data->address + (y * data->length + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int		print_picture(t_all *all)
{
	t_ray ray;

	move_front(all);
	rotate(all);
	move_sides(all);
	all->apparition.image = mlx_new_image(all->mlx, all->map.x, all->map.y);
	all->apparition.address = mlx_get_data_addr(all->apparition.image,
		&all->apparition.bpp, &all->apparition.length, &all->apparition.endian);
	ray_tex(all, &ray);
	ray_sprt(all);
	mlx_put_image_to_window(all->mlx, all->win, all->apparition.image, 0, 0);
	mlx_destroy_image(all->mlx, all->apparition.image);
	return (0);
}
