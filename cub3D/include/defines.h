/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:30:02 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/01 15:30:02 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/* window size ------------------------------------------------------------- */
# define WIN_W 1280
# define WIN_H 720

/* ray-casting -------------------------------------------------------------- */
# define FOV 0.66
# define TEX_SIZE 64

# define MOVE_SPEED 0.05
# define ROT_SPEED 0.05
# define EPS 1e-6

/* keycodes (X11 vs macOS) ------------------------------------------------- */
# ifdef __APPLE__
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_ESC 53
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
# else
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_ESC 65307
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
# endif

# ifndef COLLISION_RADIUS
#  define COLLISION_RADIUS 0.20
# endif

# ifndef MAX_MOVE_STEP
#  define MAX_MOVE_STEP 0.25
# endif

# ifndef MIN_MOVE_DISTANCE
#  define MIN_MOVE_DISTANCE 1e-6
# endif

#endif
