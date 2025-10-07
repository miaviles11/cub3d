/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:50:22 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/07 11:53:09 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	grow_grid(char ***grid, int *cap)
{
	char	**tmp;
	int		i;

	tmp = (char **)malloc(sizeof(char *) * ((*cap * 2) + 1));
	if (!tmp)
		return (-1);
	i = 0;
	while (i < *cap)
	{
		tmp[i] = (*grid)[i];
		++i;
	}
	free(*grid);
	*grid = tmp;
	*cap *= 2;
	return (0);
}

char	*trim_line(char *dup)
{
	char	*end;

	end = dup + ft_strlen(dup) - 1;
	while (end >= dup && (*end == '\n' || *end == '\r'))
		*end-- = '\0';
	return (dup);
}

int	push_line(char *src, t_map_builder *mb)
{
	char	*dup;
	int		len;

	if (mb->h >= mb->cap && grow_grid(&mb->grid, &mb->cap))
		return (-1);
	dup = ft_strdup(src);
	if (!dup)
		return (-1);
	dup = trim_line(dup);
	mb->grid[mb->h] = dup;
	len = ft_strlen(dup);
	if (len > mb->w)
		mb->w = len;
	++(mb->h);
	return (0);
}

int	skip_to_map(int fd, char **line)
{
	*line = get_next_line(fd);
	while (*line && !is_map_line(*line))
	{
		free(*line);
		*line = get_next_line(fd);
	}
	return (0);
}

int	read_map(int fd, t_map_builder *mb)
{
	char	*line;

	if (skip_to_map(fd, &line))
		return (-1);
	while (line && is_map_line(line))
	{
		if (push_line(line, mb))
			return (free(line), -1);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (0);
}
