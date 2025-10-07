/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:28:32 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/07 11:19:44 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_walk(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == 'D' || c == '2');
}

int	out_of_bounds(t_map *m, int y, int x)
{
	return (y < 0 || x < 0 || y >= m->h || x >= m->w);
}

int	is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S')
		return (1);
	if (c == 'E' || c == 'W' || c == 'D' || c == '2')
		return (1);
	return (0);
}

int	is_walkable(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	if (c == '2' || c == 'D')
		return (1);
	return (0);
}

int	touches_space_or_border(t_map *m, int y, int x)
{
	if (y == 0 || x == 0 || y == m->h - 1 || x == m->w - 1)
		return (1);
	if (m->grid[y - 1][x] == ' ' || m->grid[y + 1][x] == ' ')
		return (1);
	if (m->grid[y][x - 1] == ' ' || m->grid[y][x + 1] == ' ')
		return (1);
	return (0);
}
