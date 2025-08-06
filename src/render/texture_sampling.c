/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_sampling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:45:23 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/06 18:15:18 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* -------------------------------------------------------------------------- */
/*	Return ARGB color from a 64×64 texture.									*/
/* -------------------------------------------------------------------------- */
int	tex_sample(t_cub *cub, int id, int x, int y)
{
	if (id < 0 || id >= 5)  // CAMBIO: era >= 4, ahora >= 5
		return (0);
	if (x < 0 || x >= TEX_SIZE || y < 0 || y >= TEX_SIZE)
		return (0);
	return (cub->textures[id].img.data[y * TEX_SIZE + x]);
}
