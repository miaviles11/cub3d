/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:42:53 by miaviles          #+#    #+#             */
/*   Updated: 2025/07/17 17:43:42 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	set_hooks(t_cub *cub)
{
	if (!cub || !cub->win)
		return (-1);
	mlx_hook(cub->win, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->win, 3, 1L << 1, key_release, cub);
	mlx_hook(cub->win, 17, 0, exit_program, cub);
	mlx_loop_hook(cub->mlx, loop_hook, cub);
	return (0);
}
