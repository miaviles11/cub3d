/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:14:58 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/05 20:14:21 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	put_pixel_minimap(t_cub *c, int x, int y, int color)
{
	int	index;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	index = y * c->screen.w + x;
	c->screen.data[index] = color;
}

void	draw_minimap_border(t_cub *c)
{
	int	x;
	int	y;

	y = MINIMAP_PADDING - 1;
	while (y <= MINIMAP_PADDING + MINIMAP_SIZE)
	{
		x = MINIMAP_PADDING - 1;
		while (x <= MINIMAP_PADDING + MINIMAP_SIZE)
		{
			if (y == MINIMAP_PADDING - 1 || y == MINIMAP_PADDING + MINIMAP_SIZE
				|| x == MINIMAP_PADDING - 1 || x == MINIMAP_PADDING + MINIMAP_SIZE)
				put_pixel_minimap(c, x, y, COLOR_BORDER);
			x++;
		}
		y++;
	}
}

int	get_tile_color(t_cub *c, int map_x, int map_y)
{
	char	tile;

	if (map_x < 0 || map_x >= c->map.w || map_y < 0 || map_y >= c->map.h)
		return (COLOR_WALL);
	tile = c->map.grid[map_y][map_x];
	if (tile == '1')
		return (COLOR_WALL);
	else if (tile == 'D')
		return (COLOR_DOOR);
	else if (tile == 'S' || tile == 'T' || tile == 'E')
		return (COLOR_SPRITE);
	return (COLOR_SPACE);
}

void	draw_minimap_content(t_cub *c)
{
	int		x;
	int		y;
	int		map_x;
	int		map_y;
	int		color;

	y = 0;
	while (y < MINIMAP_SIZE)
	{
		x = 0;
		while (x < MINIMAP_SIZE)
		{
			map_x = (x * c->map.w) / MINIMAP_SIZE;
			map_y = (y * c->map.h) / MINIMAP_SIZE;
			color = get_tile_color(c, map_x, map_y);
			put_pixel_minimap(c, MINIMAP_PADDING + x, MINIMAP_PADDING + y, color);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_cub *c)
{
	if (!c || !c->screen.data)
		return ;
	draw_minimap_border(c);
	draw_minimap_content(c);
	draw_player_on_minimap(c);
}
