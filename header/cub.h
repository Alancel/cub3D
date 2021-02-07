/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 20:47:15 by alancel           #+#    #+#             */
/*   Updated: 2021/02/05 18:01:11 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdlib.h>
# include "../mlx/mlx.h"
# include <fcntl.h>
# include "../libft/libft.h"
# include <math.h>
# include "get_next_line.h"

# define MV 0.06
# define RT 0.04

typedef struct	s_ray
{
	double		camera;
	double		raydir_x;
	double		raydir_y;
	double		sidedist_x;
	double		sidedist_y;
	double		deltadist_x;
	double		deltadist_y;
	double		walldist;
	double		wall_x;
	double		step;
	double		tex_pos;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_h;
	int			start;
	int			end;
	int			tex_x;
	int			tex_y;
}				t_ray;

typedef struct	s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	float		start;
	float		end;
	void		*win;
	void		*mlx;
	void		*img;
	int			mvleft;
	int			mvright;
	int			front;
	int			back;
	int			left;
	int			right;
}				t_player;

typedef struct	s_evidence
{
	void		*image;
	char		*address;
	int			*direction;
	int			bpp;
	int			length;
	int			image_height;
	int			image_width;
	int			endian;

}				t_evidence;

typedef struct	s_map
{
	char		**mas_map;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*s;
	char		player;
	int			sx;
	int			sy;
	int			x;
	int			y;
	int			floor1;
	int			ceil1;
	int			ceil[4];
	int			floor[4];
	int			fd;
}				t_map;

typedef struct	s_sprite
{
	double		distance;
	double		sprite_x;
	double		sprite_y;
}				t_sprite;

typedef struct	s_ray_s
{
	double		sprite_x;
	double		sprite_y;
	double		inv;
	double		trans_x;
	double		trans_y;
	int			scrn_x;
	int			sprt_h;
	int			start_y;
	int			end_y;
	int			sprt_w;
	int			start_x;
	int			end_x;
}				t_ray_s;

typedef struct	s_all
{
	t_map		map;
	t_player	player;
	t_sprite	*sprite;
	t_evidence	image[5];
	t_evidence	apparition;
	t_ray		ray;
	void		*mlx;
	void		*win;
	int			sprite_quantity;
	int			zbuff[2700];
}				t_all;

int				get_next_line(int fd, char **line);
int				kick_error(int err_num);
int				put_color(t_all *all, t_ray *ray, int y);
int				print_picture(t_all *all);
int				key_press(int keycode, t_all *all);
int				key_unpress(int keycode, t_all *all);
int				ray_sprt(t_all *all);
int				pars(t_map *map);
int				parse_map(t_map *map);
void			check_scrsize(t_all *all);
void			check_fd(t_map map);
void			move_front(t_all *all);
void			move_sides(t_all *all);
void			rotate(t_all *all);
void			pars_flcl(char *str, int *red, int *green, int *blue);
void			run_mlx(t_all *all);
void			my_mlx_pixel_put(t_evidence *data, int x, int y, int color);
void			map_init(t_map *map);
void			init_direction(t_all *all, int i, int j);
void			init_image(t_all *all);
void			init_address(t_all *all);
void			init_all(t_all *all);
void			init_sprite(t_all *all);
void			parse_directions(t_map *map, char *str, int *flag);
void			ray_tex(t_all *all, t_ray *ray);
void			lining(t_all *all, t_ray *ray, int x);
void			wall_ray(t_all *all, t_ray *ray);
void			hit_ray(t_all *all, t_ray *ray);
void			step_ray(t_all *all, t_ray *ray);
void			check_first_last(char *str);
void			check_surround(t_map *map);
void			check_valid(t_map *map);
void			screen_shot(t_all *all);
void			make_map(t_map *map, t_list *list, int length);
void			parse_resolution(t_map *map, char *str, int *flag);
void			put_sprt(t_all *all, t_ray_s *rsprt, int colors, int x);
void			sprt_se(t_all *all, t_ray_s *rsprt);
void			sort_sprt(t_sprite *sprt, const int n);
char			*miss_spaces(char *str);
char			*put_line(char *line);
t_all			init(t_map map);
#endif
