/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 18:33:29 by alancel           #+#    #+#             */
/*   Updated: 2021/02/07 16:10:43 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub.h"

void		check_scrsize(t_all *all)
{
	int x;
	int y;

	mlx_get_screen_size(all->mlx, &x, &y);
	if (all->map.x > x)
		all->map.x = x;
	if (all->map.y > y)
		all->map.y = y;
}

void		check_fd(t_map map)
{
	if (map.fd < 0)
		kick_error(1);
}

static void	free_all(t_map map, t_all all)
{
	int		i;

	i = 0;
	while (map.mas_map[i])
	{
		free(map.mas_map[i]);
		i++;
	}
	free(map.mas_map);
	free(all.sprite);
	free(map.south);
	free(map.east);
	free(map.west);
	free(map.north);
	free(map.s);
	free(all.zbuff);
}

int			main(int argc, char **argv)
{
	t_map	map;
	t_all	all;
	char	*tmp;

	if (argc > 3 || argc < 2)
		kick_error(1);
	tmp = argv[1];
	while (*tmp != '.' || !*tmp)
		tmp++;
	if (ft_strncmp(tmp, ".cub", 5))
		kick_error(1);
	map.fd = open(argv[1], O_RDONLY);
	pars(&map);
	all = init(map);
	init_sprite(&all);
	if (argc == 3)
	{
		if (!(ft_strncmp(argv[2], "--save", 7)))
			screen_shot(&all);
		else
			kick_error(1);
	}
	run_mlx(&all);
	free_all(map, all);
	return (0);
}
