/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:56:20 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/08 13:17:13 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/* ========================================================================== */
/*                          WINDOW CONFIGURATION                              */
/* ========================================================================== */

# define WIN_W				1080
# define WIN_H				720

/* ========================================================================== */
/*                          RAYCASTING CONFIGURATION                          */
/* ========================================================================== */

# define FOV				0.66
# define TEX_SIZE			64

/* ========================================================================== */
/*                          PHYSICS CONSTANTS                                 */
/* ========================================================================== */

# define COLLISION_RADIUS	0.15
# define MIN_MOVE_DISTANCE	0.015
# define MOVE_SPEED			0.05
# define ROT_SPEED			0.05
# define MAX_MOVE_STEP		0.05
# define EPS				1e-6

/* ========================================================================== */
/*                          JUMP PHYSICS                                      */
/* ========================================================================== */

# define JUMP_INITIAL_SPEED		0.25
# define GRAVITY				0.015
# define JUMP_VISUAL_MULTIPLIER	40

/* ========================================================================== */
/*                          INPUT CONFIGURATION                               */
/* ========================================================================== */

# define MOUSE_SENSITIVITY	0.001

/* ========================================================================== */
/*                          SPRITE CONFIGURATION                              */
/* ========================================================================== */

# define SPRITE_SCALE		0.90
# define SPRITE_VMOVE		0.30
# define SPRITE_FRAMES		4
# define SPRITE_FPS_MS		200
# define SPRITE_SIZE		0.1
# define MAX_TEXTURES		50

/* ========================================================================== */
/*                          WEAPON CONFIGURATION                              */
/* ========================================================================== */

# define WFIRE_TICKS		6
# define WEAPON_SCALE		2

/* ========================================================================== */
/*                          CROSSHAIR CONFIGURATION                           */
/* ========================================================================== */

# define CROSSHAIR_COLOR	0x00FF00
# define CROSSHAIR_GAP		6
# define CROSSHAIR_LENGTH	8

/* ========================================================================== */
/*                          MINIMAP CONFIGURATION                             */
/* ========================================================================== */

# define MINIMAP_SIZE		150
# define MINIMAP_PADDING	10

/* ========================================================================== */
/*                          MINIMAP COLORS                                    */
/* ========================================================================== */

# define COLOR_WALL			0x4A4A4A
# define COLOR_SPACE		0x1A1A0E
# define COLOR_DOOR			0x8B4513
# define COLOR_DOOR_OPEN	0xDEB887
# define COLOR_SPRITE		0xFFD700
# define COLOR_PLAYER		0xFF4500
# define COLOR_VISITED		0x2F2F1F
# define COLOR_BORDER		0xFFFFFF

/* ========================================================================== */
/*                          KEYCODES (PLATFORM SPECIFIC)                      */
/* ========================================================================== */

# ifdef __APPLE__
#  define KEY_W				13
#  define KEY_A				0
#  define KEY_S				1
#  define KEY_D				2
#  define KEY_ESC			53
#  define KEY_LEFT			123
#  define KEY_RIGHT			124
#  define KEY_SPACE			49
#  define KEY_E				14
# else
#  define KEY_W				119
#  define KEY_A				97
#  define KEY_S				115
#  define KEY_D				100
#  define KEY_ESC			65307
#  define KEY_LEFT			65361
#  define KEY_RIGHT			65363
#  define KEY_SPACE			32
#  define KEY_E				101
# endif

#endif