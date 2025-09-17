/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:42:53 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/07 19:44:57 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* forward decls para arma/disparo (sin tocar headers) */
void	weapon_on_click(t_cub *c);
void	shoot_try(t_cub *c);
/* forward decl estrictamente necesario para el hook del ratón */
int		mouse_press(int button, int x, int y, void *param);

int	set_hooks(t_cub *cub)
{
	if (!cub || !cub->win)
		return (-1);
	mlx_hook(cub->win, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->win, 3, 1L << 1, key_release, cub);
	mlx_hook(cub->win, 17, 0, exit_program, cub);
	mlx_mouse_hook(cub->win, mouse_press, cub);
	mlx_loop_hook(cub->mlx, loop_hook, cub);
	return (0);
}

int	mouse_move(int x, int y, void *param)
{
	t_cub	*cub;
	int		dx;

	(void)y;
	cub = (t_cub *)param;
	if (cub->first_mouse)
	{
		cub->mouse_x = x;
		cub->first_mouse = 0;
		return (0);
	}
	dx = x - cub->mouse_x;
	rotate_player(&cub->player, dx * MOUSE_SENSITIVITY);
	cub->mouse_x = x;
	return (0);
}

int	mouse_press(int button, int x, int y, void *param)
{
	t_cub	*cub;

	(void)x;
	(void)y;
	cub = (t_cub *)param;
	if (button == 1)
	{
		weapon_on_click(cub);
		shoot_try(cub);
	}
	return (0);
}
