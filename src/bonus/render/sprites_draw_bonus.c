/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_draw_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:30:00 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/07 17:33:06 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static void	calculate_sprite_transform(t_cub *cub, t_sprite *sprite,
		double *transform_x, double *transform_y)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	sprite_x = sprite->pos.x - cub->player.pos.x;
	sprite_y = sprite->pos.y - cub->player.pos.y;
	inv_det = 1.0 / (cub->player.plane.x * cub->player.dir.y
			- cub->player.dir.x * cub->player.plane.y);
	*transform_x = inv_det * (cub->player.dir.y * sprite_x
			- cub->player.dir.x * sprite_y);
	*transform_y = inv_det * (-cub->player.plane.y * sprite_x
			+ cub->player.plane.x * sprite_y);
}

void	draw_sprites(t_cub *cub, int frame)
{
	int			i;
	t_sprite	*sprite;
	double		transform_x;
	double		transform_y;

	(void)frame;
	i = 0;
	while (i < cub->sprites.count)
	{
		sprite = &cub->sprites.sprites[i];
		if (sprite->loaded)
		{
			calculate_sprite_transform(cub, sprite, &transform_x, &transform_y);
			if (transform_y > 0)
				render_sprite_column(cub, sprite, transform_x, transform_y);
		}
		i++;
	}
}
