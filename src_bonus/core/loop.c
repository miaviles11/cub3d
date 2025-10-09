/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:04:46 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/09 11:12:09 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

void	weapon_draw(t_cub *c);
void	draw_crosshair(t_cub *c);
void	draw_victory_text(t_cub *cub);
void	draw_enemy_counter_text(t_cub *cub);

static int	init_screen(t_cub *cub)
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

static void	update_victory_timer(t_cub *cub)
{
	if (cub->victory_timer > 0)
	{
		cub->victory_timer--;
		if (cub->victory_timer == 0)
			cub->victory = 1;
	}
}

static void	render_victory(t_cub *cub)
{
	draw_floor_ceil(cub);
	raycaster(cub);
	draw_sprites(cub, 0);
	draw_victory_box(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.ptr, 0, 0);
	draw_victory_text(cub);
}

static void	render_game(t_cub *cub)
{
	draw_floor_ceil(cub);
	raycaster(cub);
	draw_sprites(cub, 0);
	draw_minimap(cub);
	draw_enemy_counter_box(cub);
	draw_crosshair(cub);
	weapon_draw(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.ptr, 0, 0);
	draw_enemy_counter_text(cub);
}

int	loop_hook(void *param)
{
	t_cub	*cub;
	double	dt;

	cub = (t_cub *)param;
	if (init_screen(cub))
		return (0);
	dt = timer_delta();
	update_victory_timer(cub);
	if (cub->victory)
	{
		render_victory(cub);
		return (0);
	}
	movement_update(cub);
	if (cub->door_flash_timer > 0)
		cub->door_flash_timer--;
	render_game(cub);
	timer_sleep(60, dt);
	return (0);
}
