/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:04:46 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/12 19:58:00 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int init_screen(t_cub *cub)
{
    if (cub->screen.ptr)
        return (0);

    cub->screen.ptr = mlx_new_image(cub->mlx, WIN_W, WIN_H);
    if (!cub->screen.ptr)
        return (-1);
    cub->screen.w = WIN_W;
    cub->screen.h = WIN_H;

    cub->screen.data = (int *)mlx_get_data_addr(cub->screen.ptr,
        &cub->screen.bpp, &cub->screen.line_len, &cub->screen.endian);
    return (0);
}

int	loop_hook(void *param)
{
	t_cub	*cub;
	double	dt;

	cub = (t_cub *)param;
	if (init_screen(cub))
		return (0);
	dt = timer_delta();
	movement_update(cub);
	if (cub->door_flash_timer > 0)
        cub->door_flash_timer--;
	draw_floor_ceil(cub);
	raycaster(cub);
	draw_minimap(cub);
	draw_sprites(cub, 0);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.ptr, 0, 0);
	timer_sleep(60, dt);
	return (0);
}
