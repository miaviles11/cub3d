/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:56:20 by miaviles          #+#    #+#             */
/*   Updated: 2025/07/29 17:35:30 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/* window size ------------------------------------------------------------- */
# define WIN_W      1280
# define WIN_H      720

/* ray-casting ------------------------------------------------------------- */
# define FOV        0.66
# define TEX_SIZE   64

#define COLLISION_RADIUS 0.15
#define MIN_MOVE_DISTANCE 0.015
#define MOVE_SPEED 0.03
#define ROT_SPEED 0.05
#define EPS 1e-6

/* keycodes (X11 vs macOS) ------------------------------------------------- */
# ifdef __APPLE__
#  define KEY_W     13
#  define KEY_A     0
#  define KEY_S     1
#  define KEY_D     2
#  define KEY_ESC   53
#  define KEY_LEFT  123
#  define KEY_RIGHT 124
# else
#  define KEY_W     119
#  define KEY_A     97
#  define KEY_S     115
#  define KEY_D     100
#  define KEY_ESC   65307
#  define KEY_LEFT  65361
#  define KEY_RIGHT 65363
# endif

#endif
