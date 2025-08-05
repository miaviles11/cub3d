/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:03:27 by miaviles          #+#    #+#             */
/*   Updated: 2025/07/17 18:03:28 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	exit_program(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	cub_cleanup(cub);
	exit(0);
	return (0);
}
