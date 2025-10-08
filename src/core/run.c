/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:33:04 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/08 12:15:29 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	fail(t_cub *cub, const char *msg)
{
	cub_error(cub, msg);
	cub_cleanup(cub);
	return (-1);
}

static int	init_game(t_cub *cub, const char *map_path)
{
	ft_bzero(cub, sizeof(t_cub));
	cub->map_dir = ft_dirname(map_path);
	if (!cub->map_dir)
		return (fail(cub, "malloc failed (map_dir)"));
	if (parse_scene(cub, map_path))
		return (fail(cub, "invalid .cub (identifiers/map/closure)"));
	if (init_mlx(cub))
		return (fail(cub, "mlx init failed"));
	if (init_textures(cub))
		return (fail(cub, "textures failed to load"));
	if (sprites_load_all(cub))
		return (fail(cub, "sprite textures failed to load"));
	if (init_player(cub))
		return (fail(cub, "player spawn not found"));
	return (0);
}

int	cub3d_run(const char *map_path)
{
	t_cub	cub;

	if (init_game(&cub, map_path))
		return (-1);
	if (set_hooks(&cub))
	{
		cub_cleanup(&cub);
		return (-1);
	}
	mlx_loop(cub.mlx);
	cub_cleanup(&cub);
	return (0);
}
