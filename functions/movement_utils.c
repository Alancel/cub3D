/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:29:17 by alancel           #+#    #+#             */
/*   Updated: 2021/02/02 20:28:28 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub.h"

static void		rotater(t_all *all)
{
	double olddir;
	double oldplane;

	olddir = all->player.dir_x;
	all->player.dir_x = all->player.dir_x *
	cos(-RT) - all->player.dir_y * sin(-RT);
	all->player.dir_y = olddir * sin(-RT) +
	all->player.dir_y * cos(-RT);
	oldplane = all->player.plane_x;
	all->player.plane_x = all->player.plane_x
	* cos(-RT) - all->player.plane_y * sin(-RT);
	all->player.plane_y = oldplane * sin(-RT) +
	all->player.plane_y * cos(-RT);
}

void			rotate(t_all *all)
{
	double olddir;
	double oldplane;

	if (all->player.left)
	{
		olddir = all->player.dir_x;
		all->player.dir_x = all->player.dir_x *
		cos(RT) - all->player.dir_y * sin(RT);
		all->player.dir_y = olddir * sin(RT) +
		all->player.dir_y * cos(RT);
		oldplane = all->player.plane_x;
		all->player.plane_x = all->player.plane_x *
		cos(RT) - all->player.plane_y * sin(RT);
		all->player.plane_y = oldplane * sin(RT) +
		all->player.plane_y * cos(RT);
	}
	if (all->player.right)
		rotater(all);
}
