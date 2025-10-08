/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_subdiv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:50:00 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/08 22:01:13 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

void	subdivide_movement_steps(t_cub *c, double total_dx, double total_dy,
									int steps)
{
	double	step_dx;
	double	step_dy;
	int		i;

	step_dx = total_dx / steps;
	step_dy = total_dy / steps;
	i = 0;
	while (i < steps)
	{
		apply_wall_sliding(c, step_dx, step_dy);
		i++;
	}
}

void	subdiv_move(t_cub *c, double total_dx, double total_dy)
{
	double	dist;
	int		steps;

	if (fabs(total_dx) < EPS && fabs(total_dy) < EPS)
		return ;
	if (!is_wall(c, c->player.pos.x + total_dx,
			c->player.pos.y + total_dy))
	{
		c->player.pos.x += total_dx;
		c->player.pos.y += total_dy;
		return ;
	}
	dist = sqrt(total_dx * total_dx + total_dy * total_dy);
	if (dist <= MAX_MOVE_STEP)
	{
		apply_wall_sliding(c, total_dx, total_dy);
		return ;
	}
	steps = (int)ceil(dist / MAX_MOVE_STEP);
	subdivide_movement_steps(c, total_dx, total_dy, steps);
}
