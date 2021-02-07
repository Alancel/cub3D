/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 18:49:29 by alancel           #+#    #+#             */
/*   Updated: 2021/02/02 19:31:58 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub.h"

int		key_press(int keycode, t_all *all)
{
	if (keycode == 53)
		exit(1);
	if (keycode == 1)
		all->player.back = 1;
	if (keycode == 13)
		all->player.front = 1;
	if (keycode == 0)
		all->player.mvleft = 1;
	if (keycode == 2)
		all->player.mvright = 1;
	if (keycode == 123)
		all->player.left = 1;
	if (keycode == 124)
		all->player.right = 1;
	return (0);
}

int		key_unpress(int keycode, t_all *all)
{
	if (keycode == 1)
		all->player.back = 0;
	if (keycode == 13)
		all->player.front = 0;
	if (keycode == 0)
		all->player.mvleft = 0;
	if (keycode == 2)
		all->player.mvright = 0;
	if (keycode == 123)
		all->player.left = 0;
	if (keycode == 124)
		all->player.right = 0;
	return (0);
}

void	move_front(t_all *all)
{
	if (all->player.front)
	{
		if (all->map.mas_map[(int)(all->player.x + all->player.dir_x * MV)]
		[((int)all->player.y)] == '0')
			all->player.x += all->player.dir_x * MV;
		if (all->map.mas_map[(int)all->player.x][(int)(all->player.y
		+ all->player.dir_y * MV)] == '0')
			all->player.y += all->player.dir_y * MV;
	}
	if (all->player.back)
	{
		if (all->map.mas_map[(int)(all->player.x - all->player.dir_x * MV)]
		[(int)all->player.y] == '0')
			all->player.x -= all->player.dir_x * MV;
		if (all->map.mas_map[(int)all->player.x][(int)(all->player.y
		- all->player.dir_y * MV)] == '0')
			all->player.y -= all->player.dir_y * MV;
	}
}

void	move_sides(t_all *all)
{
	if (all->player.mvleft)
	{
		if (all->map.mas_map[(int)(all->player.x - all->player.dir_y * MV)]
		[((int)all->player.y)] == '0')
			all->player.x -= all->player.dir_y * MV;
		if (all->map.mas_map[(int)all->player.x][(int)(all->player.y
		+ all->player.dir_x * MV)] == '0')
			all->player.y += all->player.dir_x * MV;
	}
	if (all->player.mvright)
	{
		if (all->map.mas_map[(int)(all->player.x + all->player.dir_y * MV)]
		[((int)all->player.y)] == '0')
			all->player.x += all->player.dir_y * MV;
		if (all->map.mas_map[(int)all->player.x][(int)(all->player.y
		- all->player.dir_x * MV)] == '0')
			all->player.y -= all->player.dir_x * MV;
	}
}
