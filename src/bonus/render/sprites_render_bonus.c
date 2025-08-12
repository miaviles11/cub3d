/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_render_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:00:00 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/12 20:16:59 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	put_pixel_sprite(t_cub *cub, int x, int y, int color)
{
	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
		cub->screen.data[y * (cub->screen.line_len / 4) + x] = color;
}

void	draw_sprite_stripe(t_cub *c, t_sprite *sp, int screen_x,
	int sprite_w, int start_y, int end_y, int sprite_h)
{
	int   start_x = screen_x - sprite_w / 2;
	int   end_x   = screen_x + sprite_w / 2;
	int   x;

	double ty = sp->distance; /* profundidad en cámara (transform_y) */

	/* mismos offsets que arriba, para que el muestreo no se desincronice */
	int jump_offset = (int)(c->player.z_offset * JUMP_VISUAL_MULTIPLIER);
	int v_move_screen = (int)(SPRITE_VMOVE / ty);

	for (x = start_x; x <= end_x; ++x)
	{
		if (x < 0 || x >= WIN_W) continue;
		/* z-buffer: si el muro está más cerca, no pintes */
		if (!(ty > 0.0 && ty < c->z_buffer[x])) continue;

		/* mapea columna -> tex_x */
		int tex_x = (int)((x - start_x) * TEX_SIZE / (double)sprite_w);
		if (tex_x < 0) tex_x = 0;
		if (tex_x >= TEX_SIZE) tex_x = TEX_SIZE - 1;

		/* stepping vertical como walls, SIN wrap */
		double v_step = (double)TEX_SIZE / (double)sprite_h;
		double v_pos  = (start_y - WIN_H / 2.0 - jump_offset
		                - v_move_screen + sprite_h / 2.0) * v_step;

		for (int y = start_y; y <= end_y; ++y)
		{
			int tex_y = (int)v_pos;             /* <-- sin & */
			if (tex_y >= 0 && tex_y < TEX_SIZE) /* <-- clamp */
			{
				int tex_id = sp->texture_ids[sp->frame_current];
				int color = tex_sample(c, tex_id, tex_x, tex_y);

				if ((color & 0x00FFFFFF) != 0 && color != 0xFF00FF)
					c->screen.data[y * (c->screen.line_len / 4) + x] = color;
			}
			v_pos += v_step;
		}
	}
}

void	render_sprite_column(t_cub *cub, t_sprite *sprite,
	double transform_x, double transform_y)
{
	int	sprite_screen_x;
	int	sprite_h;
	int	sprite_w;
	int	draw_start_y;
	int	draw_end_y;
	int	jump_offset;
	int	v_move_screen;

	/* guarda la profundidad en cámara para z-buffer en draw_sprite_stripe */
	sprite->distance = transform_y;

	sprite_screen_x = (int)((WIN_W / 2.0) * (1.0 + transform_x / transform_y));

	/* altura/anchura proyectadas */
	sprite_h = (int)fabs((WIN_H / transform_y) * SPRITE_SCALE);
	if (sprite_h < 1) sprite_h = 1;
	sprite_w = sprite_h;

	/* mismo “pitch” que muros + desplazamiento para pegarlo al suelo */
	jump_offset = (int)(cub->player.z_offset * JUMP_VISUAL_MULTIPLIER);
	v_move_screen = (int)(SPRITE_VMOVE / transform_y);

	draw_start_y = -sprite_h / 2 + WIN_H / 2 + jump_offset + v_move_screen;
	if (draw_start_y < 0) draw_start_y = 0;
	draw_end_y = sprite_h / 2 + WIN_H / 2 + jump_offset + v_move_screen;
	if (draw_end_y >= WIN_H) draw_end_y = WIN_H - 1;

	draw_sprite_stripe(cub, sprite, sprite_screen_x,
		sprite_w, draw_start_y, draw_end_y, sprite_h);
}
