/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:51:04 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/07 11:47:16 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	*try_load(void *mlx, const char *path, int *w, int *h)
{
	if (!mlx || !path || !*path)
		return (NULL);
	if (file_exists(path))
		return (mlx_xpm_file_to_image(mlx, (char *)path, w, h));
	return (NULL);
}

static void	*try_load_mapdir(t_cub *c, char *orig, t_texture *tex)
{
	void	*img;
	char	*path_mapdir;

	img = NULL;
	if (orig[0] != '/')
	{
		path_mapdir = path_join(c->map_dir, orig);
		if (path_mapdir)
		{
			img = try_load(c->mlx, path_mapdir, &tex->img.w, &tex->img.h);
			free(path_mapdir);
		}
	}
	return (img);
}

static void	*try_load_parent(t_cub *c, char *orig, t_texture *tex)
{
	void	*img;
	char	*path_parent;
	char	*parent;

	img = NULL;
	if (orig[0] != '/')
	{
		parent = ft_path_parent(c->map_dir);
		if (parent)
		{
			path_parent = path_join(parent, orig);
			free(parent);
			if (path_parent)
			{
				img = try_load(c->mlx, path_parent, &tex->img.w, &tex->img.h);
				free(path_parent);
			}
		}
	}
	return (img);
}

static int	finalize_texture(t_cub *c, t_texture *tex, void *img)
{
	if (!img || tex->img.w != TEX_SIZE || tex->img.h != TEX_SIZE)
	{
		if (img)
		{
			mlx_destroy_image(c->mlx, img);
			free(img);
		}
		return (-1);
	}
	tex->img.ptr = img;
	tex->img.data = (int *)mlx_get_data_addr(img, &tex->img.bpp,
			&tex->img.line_len, &tex->img.endian);
	if (tex->img.data)
		return (0);
	return (-1);
}

int	load_tex(t_cub *c, t_texture *tex, char *orig)
{
	void	*img;

	img = try_load(c->mlx, orig, &tex->img.w, &tex->img.h);
	if (!img)
		img = try_load_mapdir(c, orig, tex);
	if (!img)
		img = try_load_parent(c, orig, tex);
	return (finalize_texture(c, tex, img));
}
