/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:15:00 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/08 17:39:42 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* --- utils locales -------------------------------------------------------- */
int	is_nonempty_path(const char *s)
{
	return (s && s[0] != '\0');
}

void	*try_load(void *mlx, const char *path, int *w, int *h)
{
	if (!is_nonempty_path(path))
		return (NULL);
	if (!file_exists(path))
		return (NULL);
	return (mlx_xpm_file_to_image(mlx, (char *)path, w, h));
}

void	*load_direct(t_cub *c, t_texture *tex, const char *orig)
{
	return (try_load(c->mlx, orig, &tex->img.w, &tex->img.h));
}

/* drena GNL hasta EOF para liberar la stash del fd ------------------------- */
void	gnl_drain(int fd)
{
	char	*s;

	s = get_next_line(fd);
	while (s != NULL)
	{
		free(s);
		s = get_next_line(fd);
	}
}

/* true si la línea es solo espacios/tabs/CR/LF ----------------------------- */
int	is_blank_line(const char *s)
{
	while (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n')
		s++;
	return (*s == '\0');
}
