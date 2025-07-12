/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:10:32 by malja-fa          #+#    #+#             */
/*   Updated: 2025/07/12 17:10:33 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	move(float new_x, float new_y, t_cub3d *cub3d)
{
	if (get_map_char(cub3d, (int)new_x, (int)cub3d->player_y) != '1')
		cub3d->player_x = new_x;
	if (get_map_char(cub3d, (int)cub3d->player_x, (int)new_y) != '1')
		cub3d->player_y = new_y;
}

void	rotate(float old_dir_x, float old_plane_x, float rot_speed,
		t_cub3d *cub3d)
{
	cub3d->dir_x = old_dir_x * cos(rot_speed) - cub3d->dir_y * sin(rot_speed);
	cub3d->dir_y = old_dir_x * sin(rot_speed) + cub3d->dir_y * cos(rot_speed);
	cub3d->plane_x = old_plane_x * cos(rot_speed) - cub3d->plane_y
		* sin(rot_speed);
	cub3d->plane_y = old_plane_x * sin(rot_speed) + cub3d->plane_y
		* cos(rot_speed);
}
