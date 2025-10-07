/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:52:00 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/07 17:52:22 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double	ft_abs_d(double v)
{
	if (v < 0.0)
		return (-v);
	return (v);
}

double	ft_max_d(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double	ft_min_d(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}
