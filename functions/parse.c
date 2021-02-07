/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 18:38:25 by alancel           #+#    #+#             */
/*   Updated: 2021/02/05 17:54:07 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub.h"

void	parse_directions(t_map *map, char *str, int *flag)
{
	str = miss_spaces(str);
	if (!ft_strncmp("NO", str, 2) && ++*flag && !map->north)
		map->north = put_line(str + 2);
	if (!ft_strncmp("SO", str, 2) && ++*flag && !map->south)
		map->south = put_line(str + 2);
	if (!ft_strncmp("WE", str, 2) && ++*flag && !map->west)
		map->west = put_line(str + 2);
	if (!ft_strncmp("EA", str, 2) && ++*flag && !map->east)
		map->east = put_line(str + 2);
	if (!ft_strncmp("S ", str, 2) && ++*flag && !map->s)
		map->s = put_line(str + 1);
	if (ft_strchr("RFC", *str))
		parse_resolution(map, str, flag);
}

int		pars(t_map *map)
{
	char	*str;
	int		flag;
	int		mistake;

	check_fd(*map);
	flag = 0;
	mistake = 0;
	map_init(map);
	while (get_next_line(map->fd, &str))
	{
		parse_directions(map, str, &flag);
		if (flag == 8 && parse_map(map))
		{
			break ;
		}
		free(str);
	}
	free(str);
	if (flag != 8)
		kick_error(2);
	check_valid(map);
	return (0);
}

void	make_map(t_map *map, t_list *list, int length)
{
	int		i;
	t_list	*tmp;

	map->mas_map = ft_calloc(length + 1, sizeof(char *));
	i = -1;
	tmp = list;
	while (tmp)
	{
		map->mas_map[++i] = tmp->content;
		list = tmp;
		tmp = tmp->next;
		free(list);
	}
}

int		parse_map(t_map *map)
{
	t_list	*list;
	char	*str;
	int		i;

	list = NULL;
	while ((i = get_next_line(map->fd, &str) > 0))
	{
		ft_lstadd_back(&list, ft_lstnew(str));
	}
	ft_lstadd_back(&list, ft_lstnew(str));
	make_map(map, list, ft_lstsize(list));
	return (1);
}

void	parse_resolution(t_map *map, char *str, int *flag)
{
	str = miss_spaces(str);
	if (*str == 'R' && !map->x && ++*flag)
	{
		str = miss_spaces(++str);
		while (ft_isdigit(*str))
			map->x = map->x * 10 + (*(str++) - '0');
		str = miss_spaces(str);
		while (ft_isdigit(*str))
			map->y = map->y * 10 + (*(str++) - '0');
		str = miss_spaces(str);
		if (*str || map->x < 1 || map->y < 1)
			kick_error(2);
	}
	if (*str == 'C' && !map->floor[3]++ && ++*flag)
		pars_flcl(++str, &map->floor[0], &map->floor[1], &map->floor[2]);
	if (*str == 'F' && !map->ceil[3]++ && ++*flag)
		pars_flcl(++str, &map->ceil[0], &map->ceil[1], &map->ceil[2]);
	if (!ft_isdigit(*str) && *str && *str != ' ')
		kick_error(2);
}
