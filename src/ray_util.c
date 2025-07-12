/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:10:39 by malja-fa          #+#    #+#             */
/*   Updated: 2025/07/12 17:10:40 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

char	get_map_char(t_cub3d *cub3d, int x, int y)
{
	t_map	*current;

	current = cub3d->map;
	while (current && current->row_num != y)
		current = current->next;
	if (!current || x < 0 || x >= (int)ft_strlen(current->data))
		return ('1');
	return (current->data[x]);
}

void	init_ray(t_dda *dda, t_cub3d *cub3d)
{
	dda->camera_x = 2 * dda->x / (float)cub3d->map_width - 1;
	dda->ray_dir_x = cub3d->dir_x + cub3d->plane_x * dda->camera_x;
	dda->ray_dir_y = cub3d->dir_y + cub3d->plane_y * dda->camera_x;
	dda->map_x = (int)cub3d->player_x;
	dda->map_y = (int)cub3d->player_y;
	dda->hit = 0;
}

void	find_it(t_dda *dda, t_cub3d *cub3d)
{
	if (dda->side_dist_x < dda->side_dist_y)
	{
		dda->side_dist_x += dda->delta_dist_x;
		dda->map_x += dda->step_x;
		dda->side = 0;
	}
	else
	{
		dda->side_dist_y += dda->delta_dist_y;
		dda->map_y += dda->step_y;
		dda->side = 1;
	}
	if (get_map_char(cub3d, dda->map_x, dda->map_y) == '1')
		dda->hit = 1;
}
