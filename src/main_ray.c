/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaman-alrifai <yaman-alrifai@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:52:02 by yaman-alrif       #+#    #+#             */
/*   Updated: 2025/07/07 20:28:48 by yaman-alrif      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int main_1(t_cub3d *cub3d)
{
    cub3d->mlx = mlx_init(cub3d->map_width, cub3d->map_height, "Cub3D", true);
    if (!cub3d->mlx)
    {
        fprintf(stderr, "Error initializing MLX42.\n");
        return (-1);
    }
    cub3d->img = mlx_new_image(cub3d->mlx, cub3d->map_width, cub3d->map_height);
    if (!cub3d->img)
    {
        fprintf(stderr, "Error creating image.\n");
        mlx_terminate(cub3d->mlx);
        return (-1);
    }
    
    mlx_loop(cub3d->mlx);
    mlx_delete_image(cub3d->mlx, cub3d->img);
    mlx_terminate(cub3d->mlx);
    
    return (0);
}
