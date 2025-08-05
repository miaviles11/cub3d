/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:09:49 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/05 20:19:10 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	move(t_cub *c, double dx, double dy)
{
	if (fabs(dx) < MIN_MOVE_DISTANCE && fabs(dy) < MIN_MOVE_DISTANCE)
		return ;
	wall_slide_move(c, dx, dy);
}

static void	rotate(t_player *p, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir.x;
	old_plane_x = p->plane.x;
	p->dir.x = old_dir_x * cos(angle) - p->dir.y * sin(angle);
	p->dir.y = old_dir_x * sin(angle) + p->dir.y * cos(angle);
	p->plane.x = old_plane_x * cos(angle) - p->plane.y * sin(angle);
	p->plane.y = old_plane_x * sin(angle) + p->plane.y * cos(angle);
}

static void	calculate_movement_wasd(t_cub *c, double *total_dx, double *total_dy)
{
	if (c->keys.w)
	{
		*total_dx += c->player.dir.x * MOVE_SPEED;
		*total_dy += c->player.dir.y * MOVE_SPEED;
	}
	if (c->keys.s)
	{
		*total_dx -= c->player.dir.x * MOVE_SPEED;
		*total_dy -= c->player.dir.y * MOVE_SPEED;
	}
	if (c->keys.a)
	{
		*total_dx += c->player.dir.y * MOVE_SPEED;
		*total_dy -= c->player.dir.x * MOVE_SPEED;
	}
	if (c->keys.d)
	{
		*total_dx -= c->player.dir.y * MOVE_SPEED;
		*total_dy += c->player.dir.x * MOVE_SPEED;
	}
}

static void	handle_rotation(t_cub *c)
{
	if (c->keys.left)
		rotate(&c->player, -ROT_SPEED);
	if (c->keys.right)
		rotate(&c->player, ROT_SPEED);
}

int	movement_update(t_cub *c)
{
	double	total_dx;
	double	total_dy;

	total_dx = 0.0;
	total_dy = 0.0;
	calculate_movement_wasd(c, &total_dx, &total_dy);
	if (fabs(total_dx) > EPS || fabs(total_dy) > EPS)
		subdiv_move(c, total_dx, total_dy);
	handle_rotation(c);
	return (0);
}
