/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:15:00 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/07 11:47:48 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	load_door_texture(t_cub *cub)
{
	cub->textures[DIR_DOOR].path = ft_strdup("./assets/textures/door.xpm");
	if (!cub->textures[DIR_DOOR].path)
		return (-1);
	if (load_tex(cub, &cub->textures[DIR_DOOR], cub->textures[DIR_DOOR].path))
		return (-1);
	return (0);
}

int	init_textures(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (load_tex(cub, &cub->textures[i], cub->textures[i].path))
			return (-1);
		++i;
	}
	return (load_door_texture(cub));
}
