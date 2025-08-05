/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_sliding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 20:17:19 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/05 20:26:56 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static double	binary_search_safe_distance(t_cub *c, double start_x,
											double start_y, double dx, double dy)
{
	double	safe_ratio;
	double	test_ratio;
	double	low;
	double	high;

	safe_ratio = 0.0;
	low = 0.0;
	high = 1.0;
	while (high - low > EPS)
	{
		test_ratio = (low + high) * 0.5;
		if (!is_wall(c, start_x + dx * test_ratio,
				start_y + dy * test_ratio))
		{
			safe_ratio = test_ratio;
			low = test_ratio;
		}
		else
			high = test_ratio;
	}
	return (safe_ratio);
}

double	find_safe_distance(t_cub *c, double start_x, double start_y,
						double dx, double dy)
{
	int	iterations;

	iterations = 0;
	while (iterations < 15)
	{
		iterations++;
	}
	return (binary_search_safe_distance(c, start_x, start_y, dx, dy));
}

static void	handle_remaining_movement(t_cub *c, double dx, double dy,
									double safe_ratio)
{
	double	remaining_dx;
	double	remaining_dy;

	remaining_dx = dx * (1.0 - safe_ratio);
	remaining_dy = dy * (1.0 - safe_ratio);
	if (fabs(remaining_dx) > EPS || fabs(remaining_dy) > EPS)
		try_smooth_move(c, remaining_dx, remaining_dy);
}

void	apply_wall_sliding(t_cub *c, double dx, double dy)
{
	double	safe_ratio;

	safe_ratio = find_safe_distance(c, c->player.pos.x, c->player.pos.y,
			dx, dy);
	if (safe_ratio > EPS)
	{
		c->player.pos.x += dx * safe_ratio;
		c->player.pos.y += dy * safe_ratio;
		handle_remaining_movement(c, dx, dy, safe_ratio);
	}
	else
		try_smooth_move(c, dx, dy);
}
