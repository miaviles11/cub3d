/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:14:54 by miaviles          #+#    #+#             */
/*   Updated: 2025/07/29 17:33:40 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	try_move_x(t_cub *c, double dx)
{
	double	nx;
	double	reduced_dx;

	nx = c->player.pos.x + dx;
			if (!is_wall(c, nx, c->player.pos.y))
		c->player.pos.x = nx;
	else if (fabs(dx) > MIN_MOVE_DISTANCE)
	{
		reduced_dx = dx * 0.5;
		if (!is_wall(c, c->player.pos.x + reduced_dx, c->player.pos.y))
			c->player.pos.x = c->player.pos.x + reduced_dx;
	}
}

static void	try_move_y(t_cub *c, double dy)
{
	double	ny;
	double	reduced_dy;

	ny = c->player.pos.y + dy;
	if (!is_wall(c, c->player.pos.x, ny))
		c->player.pos.y = ny;
	else if (fabs(dy) > MIN_MOVE_DISTANCE)
	{
		reduced_dy = dy * 0.5;
		if (!is_wall(c, c->player.pos.x, c->player.pos.y + reduced_dy))
			c->player.pos.y = c->player.pos.y + reduced_dy;
	}
}

void	try_smooth_move(t_cub *c, double dx, double dy)
{
	try_move_x(c, dx);
	try_move_y(c, dy);
}
