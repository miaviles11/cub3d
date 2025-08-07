/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:50:59 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/07 19:14:56 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	set_plane(t_player *p)
{
	if (p->dir.x == -1)
		p->plane = (t_vec){0, FOV};
	else if (p->dir.x == 1)
		p->plane = (t_vec){0, -FOV};
	else if (p->dir.y == -1)
		p->plane = (t_vec){FOV, 0};
	else
		p->plane = (t_vec){-FOV, 0};
}

static void	init_data(t_cub *cub, char c, int x, int y)
{
	cub->player.pos = (t_vec){x + 0.5, y + 0.5};
	cub->map.grid[y][x] = '0';
	cub->player.dir = (t_vec){(c == 'E') - (c == 'W'),
		(c == 'S') - (c == 'N')};
	init_jump(&cub->player);
	set_plane(&cub->player);
	cub->door_flash_timer = 0;
	cub->door_flash_x = 0;
	cub->door_flash_y = 0;
}

int	init_player(t_cub *cub)
{
	int		y;
	int		x;
	char	c;

	y = -1;
	while (++y < cub->map.h)
	{
		x = -1;
		while (++x < cub->map.w)
		{
			c = cub->map.grid[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				init_data(cub, c, x, y);
				return (0);
			}
		}
	}
	return (-1);
}
