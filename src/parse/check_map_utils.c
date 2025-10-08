/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:40:05 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/08 15:47:22 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* check if a map cell is walkable */
int	is_walk(char c)
{
	return (c == '0'
		|| c == 'N'
		|| c == 'S'
		|| c == 'E'
		|| c == 'W'
		|| c == 'D'
		|| c == '2');
}

/* check if (y, x) is outside the map bounds */
int	out_of_bounds(t_map *m, int y, int x)
{
	return (y < 0
		|| x < 0
		|| y >= m->h
		|| x >= m->w);
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
