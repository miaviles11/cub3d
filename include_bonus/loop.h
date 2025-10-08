/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:33:35 by miaviles          #+#    #+#             */
/*   Updated: 2025/07/17 17:33:38 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOOP_H
# define LOOP_H

int	set_hooks(t_cub *cub);
int	loop_hook(void *param);
int	key_press(int keycode, void *param);
int	key_release(int keycode, void *param);
int	exit_program(void *param);

#endif
