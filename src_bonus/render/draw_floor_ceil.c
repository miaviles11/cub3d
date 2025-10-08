/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceil.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 20:46:22 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/08 22:01:34 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

void	draw_floor_ceil(t_cub *cub)
{
	int	y;
	int	x;
	int	color;
	int	*dst;
	int	horizon_line;

	horizon_line = WIN_H / 2 + (int)(cub->player.z_offset
			* JUMP_VISUAL_MULTIPLIER);
	y = 0;
	while (y < WIN_H)
	{
		color = cub->ceil_color;
		if (y >= horizon_line)
			color = cub->floor_color;
		x = 0;
		while (x < WIN_W)
		{
			dst = cub->screen.data + y * (cub->screen.line_len / 4) + x;
			*dst = color;
			++x;
		}
		++y;
	}
}
