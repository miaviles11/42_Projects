/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:30:07 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/01 15:30:07 by carlsanc         ###   ########.fr       */
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
