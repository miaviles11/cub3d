/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_render_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:00:00 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/07 10:07:48 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	put_pixel_sprite(t_cub *cub, int x, int y, int color)
{
	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
		cub->screen.data[y * (cub->screen.line_len / 4) + x] = color;
}

static void	init_sprite_params(t_sprite_params *p, t_cub *c, t_sprite *sp,
		int screen_x)
{
	p->start_x = screen_x - p->sprite_w / 2;
	p->end_x = screen_x + p->sprite_w / 2;
	p->ty = sp->distance;
	p->jump_offset = (int)(c->player.z_offset * JUMP_VISUAL_MULTIPLIER);
	p->v_move_screen = (int)(SPRITE_VMOVE / p->ty);
}

static void	draw_vertical_line(t_cub *c, t_sprite *sp, t_sprite_params *p,
		int x)
{
	int	y;
	int	tex_y;
	int	tex_id;
	int	color;

	p->v_pos = (p->start_y - WIN_H / 2.0 - p->jump_offset
			- p->v_move_screen + p->sprite_h / 2.0) * p->v_step;
	y = p->start_y;
	while (y <= p->end_y)
	{
		tex_y = (int)p->v_pos;
		if (tex_y >= 0 && tex_y < TEX_SIZE)
		{
			tex_id = sp->texture_ids[sp->frame_current];
			color = tex_sample(c, tex_id, p->tex_x, tex_y);
			if ((color & 0x00FFFFFF) != 0 && color != 0xFF00FF)
				c->screen.data[y * (c->screen.line_len / 4) + x] = color;
		}
		p->v_pos += p->v_step;
		y++;
	}
}

static void	process_stripe_column(t_cub *c, t_sprite *sp, t_sprite_params *p,
		int x)
{
	if (x < 0 || x >= WIN_W)
		return ;
	if (!(p->ty > 0.0 && p->ty < c->z_buffer[x]))
		return ;
	p->tex_x = (int)((x - p->start_x) * TEX_SIZE / (double)p->sprite_w);
	if (p->tex_x < 0)
		p->tex_x = 0;
	if (p->tex_x >= TEX_SIZE)
		p->tex_x = TEX_SIZE - 1;
	p->v_step = (double)TEX_SIZE / (double)p->sprite_h;
	draw_vertical_line(c, sp, p, x);
}

void	draw_sprite_stripe(t_cub *c, t_sprite *sp, int screen_x,
		t_draw_params dp)
{
	t_sprite_params	p;
	int				x;

	p.sprite_w = dp.sprite_w;
	p.sprite_h = dp.sprite_h;
	p.start_y = dp.start_y;
	p.end_y = dp.end_y;
	init_sprite_params(&p, c, sp, screen_x);
	x = p.start_x;
	while (x <= p.end_x)
	{
		process_stripe_column(c, sp, &p, x);
		x++;
	}
}

static void	init_render_params(t_render_params *rp, t_cub *cub,
		double transform_x, double transform_y)
{
	rp->sprite_screen_x = (int)((WIN_W / 2.0) * (1.0 + transform_x
				/ transform_y));
	rp->sprite_h = (int)fabs((WIN_H / transform_y) * SPRITE_SCALE);
	if (rp->sprite_h < 1)
		rp->sprite_h = 1;
	rp->sprite_w = rp->sprite_h;
	rp->jump_offset = (int)(cub->player.z_offset * JUMP_VISUAL_MULTIPLIER);
	rp->v_move_screen = (int)(SPRITE_VMOVE / transform_y);
}

static void	init_draw_params(t_draw_params *dp, t_render_params *rp)
{
	dp->start_y = -rp->sprite_h / 2 + WIN_H / 2 + rp->jump_offset
		+ rp->v_move_screen;
	if (dp->start_y < 0)
		dp->start_y = 0;
	dp->end_y = rp->sprite_h / 2 + WIN_H / 2 + rp->jump_offset
		+ rp->v_move_screen;
	if (dp->end_y >= WIN_H)
		dp->end_y = WIN_H - 1;
	dp->sprite_w = rp->sprite_w;
	dp->sprite_h = rp->sprite_h;
}

void	render_sprite_column(t_cub *cub, t_sprite *sprite, double transform_x,
		double transform_y)
{
	t_render_params	rp;
	t_draw_params	dp;

	sprite->distance = transform_y;
	init_render_params(&rp, cub, transform_x, transform_y);
	init_draw_params(&dp, &rp);
	draw_sprite_stripe(cub, sprite, rp.sprite_screen_x, dp);
}