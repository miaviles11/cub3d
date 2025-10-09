/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:15:00 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/09 10:38:25 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

void	*load_from_mapdir(t_cub *c, t_texture *tex,
		const char *orig, char **out_path)
{
	void	*img;

	*out_path = NULL;
	if (!orig || orig[0] == '/')
		return (NULL);
	*out_path = path_join(c->map_dir, orig);
	if (!*out_path)
		return (NULL);
	img = try_load(c->mlx, *out_path, &tex->img.w, &tex->img.h);
	return (img);
}
