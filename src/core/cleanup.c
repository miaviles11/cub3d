/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:47:39 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/09 14:26:24 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	free_grid(char **grid)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		++i;
	}
	free(grid);
}

static void	free_textures(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < cub->texture_count)
	{
		if (cub->textures[i].img.ptr)
			mlx_destroy_image(cub->mlx, cub->textures[i].img.ptr);
		free(cub->textures[i].path);
		++i;
	}
}

static void	free_doors(t_door_list *doors)
{
	if (doors->doors)
	{
		free(doors->doors);
		doors->doors = NULL;
	}
	doors->count = 0;
	doors->capacity = 0;
}

void	cub_cleanup(t_cub *cub)
{
	if (!cub)
		return ;
	free(cub->map_dir);
	free_grid(cub->map.grid);
	free_textures(cub);
	free_doors(&cub->doors);
	if (cub->screen.ptr)
		mlx_destroy_image(cub->mlx, cub->screen.ptr);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->mlx)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
}