/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:56:20 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/05 20:48:08 by miaviles         ###   ########.fr       */
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
#define MOVE_SPEED 0.05
#define ROT_SPEED 0.05
#define MAX_MOVE_STEP 0.05
#define EPS 1e-6

/* Jump physics ------------------------------------------------------------ */
#define JUMP_INITIAL_SPEED    0.25
#define GRAVITY              0.015
#define JUMP_VISUAL_MULTIPLIER  40

/* Minimap */
#define MINIMAP_SIZE     150
#define MINIMAP_PADDING  10
#define COLOR_WALL       0x4A4A4A  /* Piedra gris oscuro */
#define COLOR_SPACE      0x1A1A0E  /* Suelo de mazmorra */
#define COLOR_DOOR       0x8B4513  /* Madera de roble */
#define COLOR_SPRITE     0xFFD700  /* Oro (tesoros/objetos) */
#define COLOR_PLAYER     0xFF4500  /* Antorcha naranja */
#define COLOR_VISITED    0x2F2F1F  /* Suelo pisado */
#define COLOR_BORDER     0xFFFFFF  /* Marco de madera */

/* keycodes (X11 vs macOS) ------------------------------------------------- */
# ifdef __APPLE__
#  define KEY_W     13
#  define KEY_A     0
#  define KEY_S     1
#  define KEY_D     2
#  define KEY_ESC   53
#  define KEY_LEFT  123
#  define KEY_RIGHT 124
#  define KEY_SPACE 49
# else
#  define KEY_W     119
#  define KEY_A     97
#  define KEY_S     115
#  define KEY_D     100
#  define KEY_ESC   65307
#  define KEY_LEFT  65361
#  define KEY_RIGHT 65363
#  define KEY_SPACE 32
# endif

#endif