/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:13:00 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/07 11:53:37 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:31:19 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/09 14:15:00 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include  <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include <sys/time.h>
# include <mlx.h>
# include "libft.h"

# include "defines.h"
# include "enums.h"
# include "structs.h"
# include "loop.h"
# include "mlx_custom.h"
# include "path_utils.h"

/* -------------------------------------------------------------------------- */
/*  High-level                                                               */
/* -------------------------------------------------------------------------- */
int		cub3d_run(const char *map_path);
void	cub_cleanup(t_cub *cub);

/* -------------------------------------------------------------------------- */
/*  Init                                                                     */
/* -------------------------------------------------------------------------- */
int		init_mlx(t_cub *cub);
int		init_textures(t_cub *cub);
int		init_player(t_cub *cub);
int		init_map(t_cub *cub, const char *path);
int		grow_grid(char ***grid, int *cap);
char	*trim_line(char *dup);
int		push_line(char *src, t_map_builder *mb);
int		skip_to_map(int fd, char **line);
int		read_map(int fd, t_map_builder *mb);

/* -------------------------------------------------------------------------- */
/*  Timing                                                                   */
/* -------------------------------------------------------------------------- */
double	timer_delta(void);
void	timer_sleep(long target_fps, double dt);

/* -------------------------------------------------------------------------- */
/*  Parsing                                                                  */
/* -------------------------------------------------------------------------- */
int		parse_scene(t_cub *cub, const char *path);
int		parse_color_line(int *dst, char *l);
int		parse_texture_line(t_cub *cub, char *l);
int		normalize_map(t_map *map);
int		check_map(t_cub *cub);
int		is_map_line(const char *s);
int		parse_doors(t_cub *cub);
int		parse_sprites(t_cub *cub);

/* -------------------------------------------------------------------------- */
/*  Utils (parse)                                                            */
/* -------------------------------------------------------------------------- */
char	*skip_spaces(char *s);
int		parse_int(const char **str, int *out);

/* -------------------------------------------------------------------------- */
/*  Utils (map)                                                              */
/* -------------------------------------------------------------------------- */
int		is_walk(char c);
int		out_of_bounds(t_map *m, int y, int x);
int		is_valid_char(char c);
int		is_walkable(char c);
int		touches_space_or_border(t_map *m, int y, int x);

/* -------------------------------------------------------------------------- */
/*  Texture Management                                                        */
/* -------------------------------------------------------------------------- */
int		init_texture_array(t_cub *cub);
int		add_texture_to_array(t_cub *cub, t_texture *tex);
int		load_tex(t_cub *c, t_texture *tex, char *orig);
int		tex_sample(t_cub *cub, int id, int x, int y);
int		init_textures(t_cub *cub);

/* -------------------------------------------------------------------------- */
/*  Physics - Movement & Collision                                           */
/* -------------------------------------------------------------------------- */
void	init_jump(t_player *player);
void	update_jump(t_cub *c);
int		is_wall(t_cub *c, double x, double y);
void	wall_slide_move(t_cub *c, double dx, double dy);
void	apply_wall_sliding(t_cub *c, double dx, double dy);
void	subdiv_move(t_cub *c, double total_dx, double total_dy);
void	try_smooth_move(t_cub *c, double dx, double dy);
void	rotate_player(t_player *p, double angle); 
void	move(t_cub *c, double dx, double dy);
int		movement_update(t_cub *c);
int		check_sprite_collision(t_cub *c, double x, double y);
double	find_safe_distance(t_cub *c, t_move_data *md);
void	apply_wall_sliding(t_cub *c, double dx, double dy);

/* -------------------------------------------------------------------------- */
/*  Doors System                                                             */
/* -------------------------------------------------------------------------- */
void	handle_door_interaction(t_cub *cub);
int		is_door_position(t_cub *c, int x, int y);

/* -------------------------------------------------------------------------- */
/*  Sprites System                                                           */
/* -------------------------------------------------------------------------- */
int		load_texture_image(t_cub *cub, const char *path, int index);
char	*create_sprite_path(int frame_index);
int		load_single_frame(t_cub *cub, t_sprite *sprite, int i, int *counter);
void	init_sprite_data(t_sprite *sprite);
int		load_sprite_frames(t_cub *cub, t_sprite *sprite, int *tex_counter);
void	init_fallback_sprite(t_sprite *sprite);
int		load_sprite_safe(t_cub *cub, t_sprite *sprite, int *tex_counter);
int		sprites_load_all(t_cub *cub);
void	draw_sprites(t_cub *cub, int frame);

/* -------------------------------------------------------------------------- */
/*  Input - Mouse & Keyboard                                                 */
/* -------------------------------------------------------------------------- */
int		mouse_move(int x, int y, void *param);

/* -------------------------------------------------------------------------- */
/*  Rendering - Main                                                         */
/* -------------------------------------------------------------------------- */
void	draw_floor_ceil(t_cub *cub);
void	raycaster(t_cub *cub);
void	draw_walls(t_cub *c, int x, t_ray *r);
double	non_zero(double v);
void	set_step_side(t_cub *c, t_ray *r);
void	set_ray_dist(t_cub *c, t_ray *r);
void	set_tex_info(t_cub *c, t_ray *r);

/* ========================================================================== */
/*                            WALL DRAWING STRUCTURES                         */
/* ========================================================================== */

typedef struct s_wall_draw
{
	int		x;
	t_ray	*r;
	int		start;
	int		end;
	double	step;
	double	tex_pos;
}	t_wall_draw;

/* -------------------------------------------------------------------------- */
/*  Rendering - Minimap                                                      */
/* -------------------------------------------------------------------------- */
void	put_pixel_minimap(t_cub *cub, int x, int y, int color);
void	draw_minimap_border(t_cub *c);
int		get_tile_color(t_cub *c, int map_x, int map_y);
void	draw_minimap_content(t_cub *c);
void	draw_minimap(t_cub *c);
void	draw_player_on_minimap(t_cub *c);

/* -------------------------------------------------------------------------- */
/*  Utils (error / free)                                                     */
/* -------------------------------------------------------------------------- */
int		cub_error(t_cub *cub, const char *msg);
void	free_arr(char **arr);

/* -------------------------------------------------------------------------- */
/*  Vector operations                                                         */
/* -------------------------------------------------------------------------- */
t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_mul(t_vec v, double s);
double	vec_len(t_vec v);
t_vec	vec_norm(t_vec v);

/* -------------------------------------------------------------------------- */
/*  Math helpers                                                              */
/* -------------------------------------------------------------------------- */
double	ft_abs_d(double v);
double	ft_max_d(double a, double b);
double	ft_min_d(double a, double b);


void	put_pixel_sprite(t_cub *cub, int x, int y, int color);
void	draw_sprite_stripe(t_cub *c, t_sprite *sp, int screen_x,
			t_draw_params dp);
void	render_sprite_column(t_cub *cub, t_sprite *sprite, double transform_x,
			double transform_y);

#endif