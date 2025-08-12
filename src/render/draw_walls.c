/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 20:47:49 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/12 19:43:55 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	if (x < 0 || x >= img->w || y < 0 || y >= img->h)
		return ;
	img->data[y * (img->line_len / 4) + x] = color;
}

static void	draw_slice(t_cub *c, int x, t_ray *r,
		int start, int end, double step, double tex_pos)
{
	int	y;
	int	tex_y;
	int	color;

	y = start;
	while (y < end)
	{
		tex_y = (int)tex_pos & (TEX_SIZE - 1);
		color = tex_sample(c, r->tex_id, r->tex_x, tex_y);
		if (r->side_hit == 1)
			color = (color >> 1) & 8355711;
		put_pixel(&c->screen, x, y, color);
		tex_pos += step;
		++y;
	}
}

/* -------------------------------------------------------------------------- */
/*	Draw one textured vertical column                                         */
/* -------------------------------------------------------------------------- */
void	draw_walls(t_cub *c, int x, t_ray *r)
{
	int		line_h;
	int		start;
	int		end;
	int		jump_offset;
	double	step;
	double	tex_pos;

	line_h = (int)(WIN_H / r->dist);
	if (line_h < 1)
		line_h = 1;

	// Aplicar el mismo offset de salto que al suelo/techo
	jump_offset = (int)(c->player.z_offset * JUMP_VISUAL_MULTIPLIER);
	
	start = -line_h / 2 + WIN_H / 2 + jump_offset;
	if (start < 0)
		start = 0;
	end = line_h / 2 + WIN_H / 2 + jump_offset;
	if (end >= WIN_H)
		end = WIN_H - 1;

	step = (double)TEX_SIZE / line_h;
	tex_pos = (start - WIN_H / 2 - jump_offset + line_h / 2) * step;

	draw_slice(c, x, r, start, end, step, tex_pos);
}
