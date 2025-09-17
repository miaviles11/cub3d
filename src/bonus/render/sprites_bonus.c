/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:01:53 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/12 18:41:42 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static void	calculate_sprite_distances(t_cub *cub)
{
	int		i;
	double	dx;
	double	dy;

	i = 0;
	while (i < cub->sprites.count)
	{
		if (cub->sprites.sprites[i].frame_count <= 0)
			cub->sprites.sprites[i].distance = -1.0;
		else
		{
			dx = cub->sprites.sprites[i].pos.x - cub->player.pos.x;
			dy = cub->sprites.sprites[i].pos.y - cub->player.pos.y;
			cub->sprites.sprites[i].distance = dx * dx + dy * dy;
		}
		i++;
	}
}

static void	sort_sprites_by_distance(t_cub *cub)
{
	int			i;
	int			j;
	t_sprite	temp;

	i = 0;
	while (i < cub->sprites.count - 1)
	{
		j = 0;
		while (j < cub->sprites.count - i - 1)
		{
			if (cub->sprites.sprites[j].distance
				< cub->sprites.sprites[j + 1].distance)
			{
				temp = cub->sprites.sprites[j];
				cub->sprites.sprites[j] = cub->sprites.sprites[j + 1];
				cub->sprites.sprites[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	update_sprite_animation(t_sprite *sprite, int current_time)
{
	if (current_time - sprite->last_update > SPRITE_FPS_MS)
	{
		sprite->frame_current = (sprite->frame_current + 1)
			% sprite->frame_count;
		sprite->last_update = current_time;
	}
}

static void	draw_single_sprite(t_cub *cub, t_sprite *sprite)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;

	sprite_x = sprite->pos.x - cub->player.pos.x;
	sprite_y = sprite->pos.y - cub->player.pos.y;
	inv_det = 1.0 / (cub->player.plane.x * cub->player.dir.y
			- cub->player.dir.x * cub->player.plane.y);
	transform_x = inv_det * (cub->player.dir.y * sprite_x
			- cub->player.dir.x * sprite_y);
	transform_y = inv_det * (-cub->player.plane.y * sprite_x
			+ cub->player.plane.x * sprite_y);
	if (transform_y > 0)
		render_sprite_column(cub, sprite, transform_x, transform_y);
}

void	draw_sprites(t_cub *cub, int current_time)
{
	int	i;

	calculate_sprite_distances(cub);
	sort_sprites_by_distance(cub);
	i = 0;
	while (i < cub->sprites.count)
	{
		if (cub->sprites.sprites[i].frame_count > 0)
		{
			update_sprite_animation(&cub->sprites.sprites[i], current_time);
			draw_single_sprite(cub, &cub->sprites.sprites[i]);
		}
		i++;
	}
}
