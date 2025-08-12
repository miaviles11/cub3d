/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:15:47 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/12 19:11:54 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static int	load_sprite_texture(t_cub *cub, const char *path, int index)
{
	t_texture	*tex;
	void		*img;
	int			w;
	int			h;

	if (index >= MAX_TEXTURES)
		return (-1);
	
	tex = &cub->textures[index];
	img = mlx_xpm_file_to_image(cub->mlx, (char *)path, &w, &h);
	if (!img)
		return (-1);
	
	tex->img.ptr = img;
	tex->img.w = w;
	tex->img.h = h;
	tex->img.data = (int *)mlx_get_data_addr(img, &tex->img.bpp,
			&tex->img.line_len, &tex->img.endian);
	
	if (!tex->img.data)
	{
		mlx_destroy_image(cub->mlx, img);
		return (-1);
	}
	return (0);
}

static char	*create_sprite_path(int frame_index)
{
	char	*num_str;
	char	*temp;
	char	*path;

	num_str = ft_itoa(frame_index);
	if (!num_str)
		return (NULL);
	temp = ft_strjoin("./assets/textures/enemy_idle_", num_str);
	free(num_str);
	if (!temp)
		return (NULL);
	path = ft_strjoin(temp, ".xpm");
	free(temp);
	return (path);
}

// Función pública que usa la firma del header
int	load_sprite_frames(t_cub *cub, t_sprite *sprite)
{
	char	*path;
	int		i;
	static int sprite_tex_counter = 10; // Empezar en índice 10

	sprite->texture_ids = malloc(sizeof(int) * SPRITE_FRAMES);
	if (!sprite->texture_ids)
		return (-1);
	
	i = 0;
	while (i < SPRITE_FRAMES)
	{
		path = create_sprite_path(i);
		if (!path)
		{
			// Si falla, usar textura por defecto
			sprite->texture_ids[i] = DIR_NORTH;
		}
		else
		{
			// Intentar cargar la textura
			if (load_sprite_texture(cub, path, sprite_tex_counter) == -1)
				sprite->texture_ids[i] = DIR_NORTH; // Fallback
			else
			{
				sprite->texture_ids[i] = sprite_tex_counter;
				sprite_tex_counter++;
			}
			free(path);
		}
		i++;
	}
	
	sprite->frame_count = SPRITE_FRAMES;
	sprite->frame_current = 0;
	sprite->last_update = 0;
	sprite->loaded = 1;
	
	return (0);
}

int	sprites_load_all(t_cub *cub)
{
	int			i;
	t_sprite	*sprite;

	i = 0;
	while (i < cub->sprites.count)
	{
		sprite = &cub->sprites.sprites[i];
		if (!sprite->loaded)
		{
			if (load_sprite_frames(cub, sprite) == -1)
			{
				sprite->texture_ids = malloc(sizeof(int) * SPRITE_FRAMES);
				if (sprite->texture_ids)
				{
					for (int j = 0; j < SPRITE_FRAMES; j++)
						sprite->texture_ids[j] = DIR_NORTH;
					sprite->frame_count = SPRITE_FRAMES;
					sprite->loaded = 1;
				}
			}
		}
		i++;
	}
	return (0);
}