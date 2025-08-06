/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:35:43 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/06 17:35:47 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_ray
{
	t_vec	dir;
	t_vec	side;
	t_vec	delta;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side_hit;
	double	dist;
	int		tex_id;
	int		tex_x;
}	t_ray;

typedef struct s_img
{
	void	*ptr;
	int		*data;
	int		w;
	int		h;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_texture
{
	t_img	img;
	char	*path;
}	t_texture;

typedef struct s_map
{
	char	**grid;
	int		w;
	int		h;
}	t_map;

typedef struct s_player
{
	t_vec	pos;
	t_vec	dir;
	t_vec	plane;
	double	z_offset;
	double	jump_speed;
	int		is_jumping;
}	t_player;

typedef struct s_door
{
	t_vec	pos;
	int		is_open;
	char	original;
}	t_door;

typedef struct s_door_list
{
	t_door	*doors;
	int		count;
	int		capacity;
}	t_door_list;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
	int	space;
	int	e;
}	t_keys;

typedef struct s_cub
{
	void			*mlx;
	void			*win;
	t_img			screen;
	t_texture		textures[5];
	t_map			map;
	t_player		player;
	t_keys			keys;
	t_door_list		doors;
	int				floor_color;
	int				ceil_color;
	char			*map_dir;
}	t_cub;

#endif