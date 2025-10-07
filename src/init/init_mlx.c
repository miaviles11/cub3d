/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:50:12 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/07 20:01:01 by miaviles         ###   ########.fr       */
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

int	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (-1);
	cub->win = mlx_new_window(cub->mlx, WIN_W, WIN_H, "cub3D");
	if (!cub->win)
		return (-1);
	cub->screen.ptr = NULL;
	setup_mouse(cub);
	return (0);
}
