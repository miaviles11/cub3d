/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_render_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:00:00 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/09 19:48:25 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static void	put_pixel_sprite(t_cub *cub, int x, int y, int color)
{
	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H && color != 0x000000)
		cub->screen.data[y * (cub->screen.line_len / 4) + x] = color;
}

static void draw_sprite_stripe(t_cub *cub, t_sprite *sprite, int sprite_screen_x, 
    int sprite_width, int draw_start_y, int draw_end_y, int sprite_height, double transform_y)
{
    int     stripe;
    int     y;
    int     tex_x;
    int     tex_y;
    int     color;
    
    stripe = sprite_screen_x - sprite_width / 2;
    while (stripe < sprite_screen_x + sprite_width / 2)
    {
        tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) 
            * TEX_SIZE / sprite_width) / 256;
        if (stripe > 0 && stripe < WIN_W && tex_x >= 0 && tex_x < TEX_SIZE 
            && transform_y < cub->z_buffer[stripe])  // ← Importante
        {
            y = draw_start_y;
            while (y < draw_end_y)
            {
                tex_y = (((y * 256 - WIN_H * 128 + sprite_height * 128) 
                    * TEX_SIZE) / sprite_height) / 256;
                if (tex_y >= 0 && tex_y < TEX_SIZE)
                {
                    color = tex_sample(cub, sprite->texture_ids[sprite->frame_current], 
                        tex_x, tex_y);
                    put_pixel_sprite(cub, stripe, y, color);
                }
                y++;
            }
        }
        stripe++;
    }
}

void render_sprite_column(t_cub *cub, t_sprite *sprite, double transform_x, double transform_y)
{
    int     sprite_screen_x;
    int     sprite_height;
    int     draw_start_y;
    int     draw_end_y;
    int     sprite_width;
    
    sprite_screen_x = (int)((WIN_W / 2) * (1 + transform_x / transform_y));
    sprite_height = abs((int)(WIN_H / transform_y));
    
    draw_start_y = -sprite_height / 2 + WIN_H / 2;
    if (draw_start_y < 0)
        draw_start_y = 0;
    draw_end_y = sprite_height / 2 + WIN_H / 2;
    if (draw_end_y >= WIN_H)
        draw_end_y = WIN_H - 1;
    
    sprite_width = abs((int)(WIN_H / transform_y));
    draw_sprite_stripe(cub, sprite, sprite_screen_x, sprite_width, 
        draw_start_y, draw_end_y, sprite_height, transform_y);
}
