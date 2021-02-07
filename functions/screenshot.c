/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 20:22:07 by alancel           #+#    #+#             */
/*   Updated: 2021/02/03 17:48:00 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub.h"

static int		my_get_color(t_all *all, int x, int y)
{
	char	*dst;

	dst = all->apparition.address + (y * all->apparition.length
	+ x * (all->apparition.bpp / 8));
	return (*(unsigned int*)dst);
}

static void		init_header(unsigned char *mas_heder, int size, t_all *all)
{
	mas_heder[0] = (unsigned char)'B';
	mas_heder[1] = (unsigned char)'M';
	mas_heder[2] = (unsigned char)size;
	mas_heder[3] = (unsigned char)(size >> 8);
	mas_heder[4] = (unsigned char)(size >> 16);
	mas_heder[5] = (unsigned char)(size >> 24);
	mas_heder[10] = (unsigned char)54;
	mas_heder[14] = (unsigned char)40;
	mas_heder[18] = (unsigned char)all->map.x;
	mas_heder[19] = (unsigned char)(all->map.x >> 8);
	mas_heder[20] = (unsigned char)(all->map.x >> 16);
	mas_heder[21] = (unsigned char)(all->map.x >> 24);
	mas_heder[22] = (unsigned char)all->map.y;
	mas_heder[23] = (unsigned char)(all->map.y >> 8);
	mas_heder[24] = (unsigned char)(all->map.y >> 16);
	mas_heder[25] = (unsigned char)(all->map.y >> 24);
	mas_heder[26] = (unsigned char)1;
	mas_heder[28] = (unsigned char)24;
}

static void		put_img_skrin(t_all *all, int fd)
{
	int		color;
	int		x;
	int		y;
	int		size_x;

	color = 0;
	x = 0;
	y = all->map.y - 1;
	size_x = all->map.x;
	while (y >= 0)
	{
		while (x < size_x)
		{
			color = my_get_color(all, x, y);
			write(fd, &color, 3);
			x++;
		}
		y--;
		x = 0;
	}
}

void			screen_shot(t_all *all)
{
	int				fd;
	unsigned char	mas_heder[54];
	int				count;
	int				size;

	if (all->map.x % 4)
		all->map.x = all->map.x - (all->map.x % 4);
	all->apparition.image = mlx_new_image(all->mlx,
	all->map.x, all->map.y);
	all->apparition.address = mlx_get_data_addr(all->apparition.image,
	&all->apparition.bpp, &all->apparition.length, &all->apparition.endian);
	print_picture(all);
	size = all->map.x * all->map.y + 54;
	count = 0;
	if (!(fd = open("./screenshot.bmp", O_RDWR | O_CREAT, 0666)))
		kick_error(1);
	while (count < 54)
		mas_heder[count++] = (unsigned char)0;
	init_header(mas_heder, size, all);
	write(fd, mas_heder, 54);
	put_img_skrin(all, fd);
	close(fd);
	exit(0);
}
