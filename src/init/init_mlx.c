/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:50:12 by miaviles          #+#    #+#             */
/*   Updated: 2025/07/17 17:50:15 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (-1);
	cub->win = mlx_new_window(cub->mlx, WIN_W, WIN_H, "cub3D");
	if (!cub->win)
		return (-1);
	cub->screen.ptr = NULL;
	return (0);
}