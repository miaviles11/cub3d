/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:31:19 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/06 16:58:19 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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
int     cub3d_run(const char *map_path);
void    cub_cleanup(t_cub *cub);

/* -------------------------------------------------------------------------- */
/*  Init                                                                     */
/* -------------------------------------------------------------------------- */
int     init_mlx(t_cub *cub);
int     init_textures(t_cub *cub);
int     init_player(t_cub *cub);
int     init_map(t_cub *cub, const char *path);

/* -------------------------------------------------------------------------- */
/*  Timing                                                                   */
/* -------------------------------------------------------------------------- */
double  timer_delta(void);
void    timer_sleep(long target_fps, double dt);

/* -------------------------------------------------------------------------- */
/*  Parsing                                                                  */
/* -------------------------------------------------------------------------- */
int     parse_scene(t_cub *cub, const char *path);
int     parse_color_line(int *dst, char *l);
int     parse_texture_line(t_cub *cub, char *l);
int     normalize_map(t_map *map);
int     check_map(t_cub *cub);
int     is_map_line(const char *s);

/* -------------------------------------------------------------------------- */
/*  Utils (parse)                                                            */
/* -------------------------------------------------------------------------- */
char    *skip_spaces(char *s);
int     parse_int(const char **str, int *out);

/* -------------------------------------------------------------------------- */
/*  Utils (map)                                                              */
/* -------------------------------------------------------------------------- */
int     is_walk(char c);
int     out_of_bounds(t_map *m, int y, int x);

/* -------------------------------------------------------------------------- */
/*  Game logic physics                                                              */
/* -------------------------------------------------------------------------- */
void    init_jump(t_player *player);
void    update_jump(t_cub *c);
int		is_wall(t_cub *c, double x, double y);
void	wall_slide_move(t_cub *c, double dx, double dy);
double	find_safe_distance(t_cub *c, double start_x, double start_y, double dx, double dy);
void	apply_wall_sliding(t_cub *c, double dx, double dy);
void	subdiv_move(t_cub *c, double total_dx, double total_dy);
void	try_smooth_move(t_cub *c, double dx, double dy);
void	move(t_cub *c, double dx, double dy);
int		movement_update(t_cub *c);

/* -------------------------------------------------------------------------- */
/*  Rendering                                                                 */
/* -------------------------------------------------------------------------- */
void    draw_floor_ceil(t_cub *cub);
void    raycaster(t_cub *cub);
int     tex_sample(t_cub *cub, int id, int x, int y);
void	draw_walls(t_cub *c, int x, t_ray *r);
void	put_pixel_minimap(t_cub *c, int x, int y, int color);
void	draw_minimap_border(t_cub *c);
int		get_tile_color(t_cub *c, int map_x, int map_y);
void	draw_minimap_content(t_cub *c);
void	draw_minimap(t_cub *c);
void	draw_player_on_minimap(t_cub *c);

/* -------------------------------------------------------------------------- */
/*  Utils (error / free)                                                      */
/* -------------------------------------------------------------------------- */
int     cub_error(t_cub *cub, const char *msg);
void    free_arr(char **arr);

/* -------------------------------------------------------------------------- */
/*  Vector operations                                                         */
/* -------------------------------------------------------------------------- */
t_vec   vec_add(t_vec a, t_vec b);
t_vec   vec_mul(t_vec v, double s);
double  vec_len(t_vec v);
t_vec   vec_norm(t_vec v);

/* -------------------------------------------------------------------------- */
/*  Math helpers                                                              */
/* -------------------------------------------------------------------------- */
double  ft_abs_d(double v);
double  ft_max_d(double a, double b);
double  ft_min_d(double a, double b);

int		parse_doors(t_cub *cub);
void	handle_door_interaction(t_cub *cub);

#endif
