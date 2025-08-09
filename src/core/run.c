/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:33:04 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/09 16:48:04 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	init_game(t_cub *cub, const char *map_path)
{
	ft_bzero(cub, sizeof(t_cub));

	cub->map_dir = ft_dirname(map_path);
	if (!cub->map_dir)
		return (-1);
	if (parse_scene(cub, map_path))
		return (-1);
	if (init_mlx(cub))
		return (-1);
	if (init_textures(cub))
		return (-1);
	if (sprites_load_all(cub)) 
		return (-1);
	if (init_player(cub))
		return (-1);
	return (0);
}

int	cub3d_run(const char *map_path)
{
	t_cub	cub;

	if (init_game(&cub, map_path))
	{
		cub_cleanup(&cub);
		return (-1);
	}
	if (set_hooks(&cub))
	{
		cub_cleanup(&cub);
		return (-1);
	}
	mlx_loop(cub.mlx);
	cub_cleanup(&cub);
	return (0);
}
