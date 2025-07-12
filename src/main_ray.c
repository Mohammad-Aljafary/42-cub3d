/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:52:02 by yaman-alrif       #+#    #+#             */
/*   Updated: 2025/07/12 17:02:50 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	delta_h(t_dda *dda)
{
	if (dda->ray_dir_x == 0)
		dda->delta_dist_x = 1e30;
	else
		dda->delta_dist_x = fabs(1 / dda->ray_dir_x);
	if (dda->ray_dir_y == 0)
		dda->delta_dist_y = 1e30;
	else
		dda->delta_dist_y = fabs(1 / dda->ray_dir_y);
}

void	delta(t_dda *dda, t_cub3d *cub3d)
{
	delta_h(dda);
	if (dda->ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (cub3d->player_x - dda->map_x) * dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0 - cub3d->player_x)
			* dda->delta_dist_x;
	}
	if (dda->ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (cub3d->player_y - dda->map_y) * dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0 - cub3d->player_y)
			* dda->delta_dist_y;
	}
}

void	start_dda(t_cub3d *cub3d)
{
	t_dda	dda;

	dda.x = 0;
	while (dda.x < cub3d->map_width)
	{
		init_ray(&dda, cub3d);
		delta(&dda, cub3d);
		while (!dda.hit)
			find_it(&dda, cub3d);
		if (dda.side == 0)
			dda.perp_wall_dist = (dda.map_x - cub3d->player_x + (1 - dda.step_x)
					/ 2) / dda.ray_dir_x;
		else
			dda.perp_wall_dist = (dda.map_y - cub3d->player_y + (1 - dda.step_y)
					/ 2) / dda.ray_dir_y;
		dda.line_height = (int)(cub3d->map_height / dda.perp_wall_dist);
		dda.draw_start = -dda.line_height / 2 + cub3d->map_height / 2;
		if (dda.draw_start < 0)
			dda.draw_start = 0;
		dda.draw_end = dda.line_height / 2 + cub3d->map_height / 2;
		if (dda.draw_end >= cub3d->map_height)
			dda.draw_end = cub3d->map_height - 1;
		start_drawing(cub3d, &dda);
		dda.x++;
	}
}

void	key_hook(void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(cub3d->mlx);
		free_cub3d(cub3d);
		exit(0);
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
		move(cub3d->player_x + cub3d->dir_x * 0.1f, cub3d->player_y
			+ cub3d->dir_y * 0.1f, cub3d);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
		move(cub3d->player_x - cub3d->dir_x * 0.1f, cub3d->player_y
			- cub3d->dir_y * 0.1f, cub3d);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
		move(cub3d->player_x + cub3d->dir_y * 0.1f, cub3d->player_y
			- cub3d->dir_x * 0.1f, cub3d);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
		move(cub3d->player_x - cub3d->dir_y * 0.1f, cub3d->player_y
			+ cub3d->dir_x * 0.1f, cub3d);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT))
		rotate(cub3d->dir_x, cub3d->plane_x, 0.05, cub3d);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_LEFT))
		rotate(cub3d->dir_x, cub3d->plane_x, -0.05, cub3d);
}

void	render_loop(void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	memset(cub3d->img->pixels, 0, cub3d->img->width * cub3d->img->height
		* sizeof(uint32_t));
	start_dda(cub3d);
}
