/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_sampling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:45:23 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/08 22:01:49 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

/* -------------------------------------------------------------------------- */
/*	Return ARGB color from a 64×64 texture.									*/
/* -------------------------------------------------------------------------- */
int	tex_sample(t_cub *cub, int id, int x, int y)
{
	t_img	*im;
	int		sx;
	int		sy;

	if (id < 0 || id >= MAX_TEXTURES)
		return (0);
	im = &cub->textures[id].img;
	if (!im->data || im->w <= 0 || im->h <= 0)
		return (0);
	sx = x;
	if (im->w != TEX_SIZE)
		sx = (x * im->w) / TEX_SIZE;
	sy = y;
	if (im->h != TEX_SIZE)
		sy = (y * im->h) / TEX_SIZE;
	if (sx < 0 || sx >= im->w || sy < 0 || sy >= im->h)
		return (0);
	return (im->data[sy * (im->line_len / 4) + sx]);
}
