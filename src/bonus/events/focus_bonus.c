/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   focus_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:55:00 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/07 19:46:00 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	focus_in(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	mlx_mouse_hide(cub->mlx, cub->win);
	mlx_mouse_move(cub->mlx, cub->win, WIN_W / 2, WIN_H / 2);
	cub->first_mouse = 1;
	return (0);
}

int	focus_out(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	mlx_mouse_show(cub->mlx, cub->win);
	return (0);
}
