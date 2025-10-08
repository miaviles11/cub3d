/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:50:12 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/08 17:18:20 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	setup_mouse(t_cub *cub)
{
	mlx_mouse_hide(cub->mlx, cub->win);
	mlx_mouse_move(cub->mlx, cub->win, WIN_W / 2, WIN_H / 2);
	cub->mouse_x = WIN_W / 2;
	cub->first_mouse = 1;
}

static int	init_zbuffer(t_cub *cub)
{
	int	i;

	cub->z_buffer = malloc(sizeof(double) * WIN_W);
	if (!cub->z_buffer)
		return (-1);
	i = 0;
	while (i < WIN_W)
	{
		cub->z_buffer[i] = 0.0;
		i++;
	}
	return (0);
}

static int	init_screen_image(t_cub *cub)
{
	cub->screen.ptr = mlx_new_image(cub->mlx, WIN_W, WIN_H);
	if (!cub->screen.ptr)
		return (-1);
	cub->screen.data = (int *)mlx_get_data_addr(cub->screen.ptr,
			&cub->screen.bpp,
			&cub->screen.line_len,
			&cub->screen.endian);
	if (!cub->screen.data)
		return (-1);
	cub->screen.w = WIN_W;
	cub->screen.h = WIN_H;
	return (0);
}

int	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (-1);
	cub->win = mlx_new_window(cub->mlx, WIN_W, WIN_H, "cub3D");
	if (!cub->win)
		return (-1);
	if (init_screen_image(cub) == -1)
		return (-1);
	if (init_zbuffer(cub) == -1)
		return (-1);
	setup_mouse(cub);
	return (0);
}
