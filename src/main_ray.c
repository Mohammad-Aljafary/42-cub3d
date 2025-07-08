/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaman-alrifai <yaman-alrifai@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:52:02 by yaman-alrif       #+#    #+#             */
/*   Updated: 2025/07/08 11:36:55 by yaman-alrif      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

char get_map_char(t_cub3d *cub3d, int x, int y)
{
    t_map *current = cub3d->map;

    while (current && current->row_num != y)
        current = current->next;
    
    if (!current || x < 0 || x >= (int)strlen(current->data))
        return '1';
    
    return current->data[x];
}

void start_dda(t_cub3d *cub3d, mlx_image_t *img)
{
    int x;
    float camera_x;
    float ray_dir_x;
    float ray_dir_y;
    int map_x;
    int map_y;
    float side_dist_x;
    float side_dist_y;
    float delta_dist_x;
    float delta_dist_y;
    int step_x;
    int step_y;
    int hit;
    int side;
    float perp_wall_dist;

    x = 0;
    while (x < cub3d->map_width)
    {
        camera_x = 2 * x / (float)cub3d->map_width - 1;
        ray_dir_x = cub3d->dir_x + cub3d->plane_x * camera_x;
        ray_dir_y = cub3d->dir_y + cub3d->plane_y * camera_x;
        map_x = (int)cub3d->player_x;
        map_y = (int)cub3d->player_y;
        if (ray_dir_x == 0)
            delta_dist_x = 1e30;
        else
            delta_dist_x = fabs(1 / ray_dir_x);
        if (ray_dir_y == 0)
            delta_dist_y = 1e30;
        else
            delta_dist_y = fabs(1 / ray_dir_y);
        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (cub3d->player_x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - cub3d->player_x) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (cub3d->player_y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - cub3d->player_y) * delta_dist_y;
        }
        hit = 0;
        while (!hit)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (get_map_char(cub3d, map_x, map_y) == '1')
                hit = 1;
        }
        if (side == 0)
            perp_wall_dist = (map_x - cub3d->player_x + (1 - step_x) / 2) / ray_dir_x;
        else
            perp_wall_dist = (map_y - cub3d->player_y + (1 - step_y) / 2) / ray_dir_y;
        int line_height = (int)(cub3d->map_height / perp_wall_dist);
        int draw_start = -line_height / 2 + cub3d->map_height / 2;
        if (draw_start < 0)
            draw_start = 0;
        int draw_end = line_height / 2 + cub3d->map_height / 2;
        if (draw_end >= cub3d->map_height)
            draw_end = cub3d->map_height - 1;
        long long color;
        if (side == 1)
            color = 0xFF0000FF;
        else
            color = 0x800000FF;
        for (int y = draw_start; y <= draw_end; y++)
        {
            mlx_put_pixel(img, x, y, color);
        }
        for (int y = 0; y < draw_start; y++)
        {
            mlx_put_pixel(img, x, y, 0x323232FF);
        }
        for (int y = draw_end + 1; y < cub3d->map_height; y++)
        {
            mlx_put_pixel(img, x, y, 0x787878FF);
        }
        x++;
    }
}

void key_hook(mlx_key_data_t keydata, void *param)
{
    t_cub3d *cub3d = (t_cub3d *)param;
    
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(cub3d->mlx);
    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
    {
        float move_speed = 0.1f;
        float rot_speed = 0.05f;
        if (keydata.key == MLX_KEY_W)
        {
            float new_x = cub3d->player_x + cub3d->dir_x * move_speed;
            float new_y = cub3d->player_y + cub3d->dir_y * move_speed;
            if (get_map_char(cub3d, (int)new_x, (int)cub3d->player_y) != '1')
                cub3d->player_x = new_x;
            if (get_map_char(cub3d, (int)cub3d->player_x, (int)new_y) != '1')
                cub3d->player_y = new_y;
        }
        else if (keydata.key == MLX_KEY_S)
        {
            float new_x = cub3d->player_x - cub3d->dir_x * move_speed;
            float new_y = cub3d->player_y - cub3d->dir_y * move_speed;
            if (get_map_char(cub3d, (int)new_x, (int)cub3d->player_y) != '1')
                cub3d->player_x = new_x;
            if (get_map_char(cub3d, (int)cub3d->player_x, (int)new_y) != '1')
                cub3d->player_y = new_y;
        }
        else if (keydata.key == MLX_KEY_A)
        {
            float old_dir_x = cub3d->dir_x;
            cub3d->dir_x = cub3d->dir_x * cos(rot_speed) - cub3d->dir_y * sin(rot_speed);
            cub3d->dir_y = old_dir_x * sin(rot_speed) + cub3d->dir_y * cos(rot_speed);
            float old_plane_x = cub3d->plane_x;
            cub3d->plane_x = cub3d->plane_x * cos(rot_speed) - cub3d->plane_y * sin(rot_speed);
            cub3d->plane_y = old_plane_x * sin(rot_speed) + cub3d->plane_y * cos(rot_speed);
        }
        else if (keydata.key == MLX_KEY_D)
        {
            float old_dir_x = cub3d->dir_x;
            cub3d->dir_x = cub3d->dir_x * cos(-rot_speed) - cub3d->dir_y * sin(-rot_speed);
            cub3d->dir_y = old_dir_x * sin(-rot_speed) + cub3d->dir_y * cos(-rot_speed);
            float old_plane_x = cub3d->plane_x;
            cub3d->plane_x = cub3d->plane_x * cos(-rot_speed) - cub3d->plane_y * sin(-rot_speed);
            cub3d->plane_y = old_plane_x * sin(-rot_speed) + cub3d->plane_y * cos(-rot_speed);
        }
    }
}

void render_loop(void *param)
{
    t_cub3d *cub3d = (t_cub3d *)param;
    mlx_image_t *img = cub3d->img;
    
    memset(img->pixels, 0, img->width * img->height * sizeof(uint32_t));
    start_dda(cub3d, img);
}

int main_1(t_cub3d *cub3d)
{
    mlx_image_t *img = mlx_new_image(cub3d->mlx, cub3d->map_width, cub3d->map_height);
    if (!img)
    {
        printf("Failed to create image\n");
        return (1);
    }
    cub3d->img = img;
    if (mlx_image_to_window(cub3d->mlx, img, 0, 0) == -1)
    {
        printf("Failed to put image to window\n");
        return (1);
    }
    mlx_key_hook(cub3d->mlx, key_hook, cub3d);
    mlx_loop_hook(cub3d->mlx, render_loop, cub3d);
    mlx_loop(cub3d->mlx);
    mlx_delete_image(cub3d->mlx, img);
    mlx_terminate(cub3d->mlx);
    return (0);
}
