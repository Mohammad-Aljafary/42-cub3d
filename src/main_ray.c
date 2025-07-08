/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaman-alrifai <yaman-alrifai@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:52:02 by yaman-alrif       #+#    #+#             */
/*   Updated: 2025/07/08 17:34:20 by yaman-alrif      ###   ########.fr       */
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

void print_texture(t_cub3d *cub3d, t_texture *texture, t_dda dda, int draw_start, int draw_end)
{
    unsigned int tex_x;
    unsigned int tex_y = 1;
    int color;
    int y;

    tex_x = (int)(texture->xpm->width * (dda.perp_wall_dist - floor(dda.perp_wall_dist)));
    y = draw_start - 1;
    while (++y < draw_end)
    {
        tex_y = (int)((y - cub3d->map_height / 2 + dda.perp_wall_dist) * texture->height / dda.perp_wall_dist);
        if (tex_y >= texture->height)
            continue;
        color = texture->pixels[tex_y * texture->width + tex_x];
        mlx_put_pixel(cub3d->img, dda.x, y, color);
    }
}

void print_floor_and_ceiling(t_cub3d *cub3d, int x, int draw_start, int draw_end)
{
    t_texture *floor_texture;
    t_texture *ceiling_texture;
    int y;
    unsigned long long   color_c;
    unsigned long long   color_f;

    floor_texture = get_name_texture(cub3d->textures, "F");
    ceiling_texture = get_name_texture(cub3d->textures, "C");
    color_c = (unsigned long long)(floor_texture->red << 16 | floor_texture->green << 8 | floor_texture->blue);
    color_f = (unsigned long long)(ceiling_texture->red << 16 | ceiling_texture->green << 8 | ceiling_texture->blue);
    y = -1;
    while (++y < cub3d->map_height)
    {
        if (y < draw_start)
        {
            mlx_put_pixel(cub3d->img, x, y, color_c);
        }
        else if (y >= draw_end)
        {
            mlx_put_pixel(cub3d->img, x, y, color_f);
        }
    }
}

void start_drawing(t_cub3d *cub3d, t_dda dda, int draw_start, int draw_end)
{
    double wall_x;
    t_texture *texture;

    if (dda.side == 0)
        wall_x = cub3d->player_y + dda.perp_wall_dist * dda.ray_dir_y;
    else
        wall_x = cub3d->player_x + dda.perp_wall_dist * dda.ray_dir_x;
    wall_x -= floor(wall_x);
    if (dda.side == 0)
    {
        if (dda.ray_dir_x < 0)
            texture = get_name_texture(cub3d->textures, "WE");
        else
            texture = get_name_texture(cub3d->textures, "EA");
    }
    else
    {
        if (dda.ray_dir_y < 0)
            texture = get_name_texture(cub3d->textures, "NO");
        else
            texture = get_name_texture(cub3d->textures, "SO");
    }
    print_texture(cub3d, texture, dda, draw_start, draw_end);
    print_floor_and_ceiling(cub3d, dda.x, draw_start, draw_end);
}

void start_dda(t_cub3d *cub3d)
{
    t_dda dda;

    dda.x = 0;
    while (dda.x < cub3d->map_width)
    {
        dda.camera_x = 2 * dda.x / (float)cub3d->map_width - 1;
        dda.ray_dir_x = cub3d->dir_x + cub3d->plane_x * dda.camera_x;
        dda.ray_dir_y = cub3d->dir_y + cub3d->plane_y * dda.camera_x;
        dda.map_x = (int)cub3d->player_x;
        dda.map_y = (int)cub3d->player_y;
        if (dda.ray_dir_x == 0)
            dda.delta_dist_x = 1e30;
        else
            dda.delta_dist_x = fabs(1 / dda.ray_dir_x);
        if (dda.ray_dir_y == 0)
            dda.delta_dist_y = 1e30;
        else
            dda.delta_dist_y = fabs(1 / dda.ray_dir_y);
        if (dda.ray_dir_x < 0)
        {
            dda.step_x = -1;
            dda.side_dist_x = (cub3d->player_x - dda.map_x) * dda.delta_dist_x;
        }
        else
        {
            dda.step_x = 1;
            dda.side_dist_x = (dda.map_x + 1.0 - cub3d->player_x) * dda.delta_dist_x;
        }
        if (dda.ray_dir_y < 0)
        {
            dda.step_y = -1;
            dda.side_dist_y = (cub3d->player_y - dda.map_y) * dda.delta_dist_y;
        }
        else
        {
            dda.step_y = 1;
            dda.side_dist_y = (dda.map_y + 1.0 - cub3d->player_y) * dda.delta_dist_y;
        }
        dda.hit = 0;
        while (!dda.hit)
        {
            if (dda.side_dist_x < dda.side_dist_y)
            {
                dda.side_dist_x += dda.delta_dist_x;
                dda.map_x += dda.step_x;
                dda.side = 0;
            }
            else
            {
                dda.side_dist_y += dda.delta_dist_y;
                dda.map_y += dda.step_y;
                dda.side = 1;
            }
            if (get_map_char(cub3d, dda.map_x, dda.map_y) == '1')
                dda.hit = 1;
        }
        if (dda.side == 0)
            dda.perp_wall_dist = (dda.map_x - cub3d->player_x + (1 - dda.step_x) / 2) / dda.ray_dir_x;
        else
            dda.perp_wall_dist = (dda.map_y - cub3d->player_y + (1 - dda.step_y) / 2) / dda.ray_dir_y;
        int line_height = (int)(cub3d->map_height / dda.perp_wall_dist);
        int draw_start = -line_height / 2 + cub3d->map_height / 2;
        if (draw_start < 0)
            draw_start = 0;
        int draw_end = line_height / 2 + cub3d->map_height / 2;
        if (draw_end >= cub3d->map_height)
            draw_end = cub3d->map_height - 1;
        start_drawing(cub3d, dda, draw_start, draw_end);
        dda.x++;
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
            float new_x = cub3d->player_x + cub3d->dir_y * move_speed;
            float new_y = cub3d->player_y - cub3d->dir_x * move_speed;
            if (get_map_char(cub3d, (int)new_x, (int)cub3d->player_y) != '1')
                cub3d->player_x = new_x;
            if (get_map_char(cub3d, (int)cub3d->player_x, (int)new_y) != '1')
                cub3d->player_y = new_y;
        }
        else if (keydata.key == MLX_KEY_D)
        {
            float new_x = cub3d->player_x - cub3d->dir_y * move_speed;
            float new_y = cub3d->player_y + cub3d->dir_x * move_speed;
            if (get_map_char(cub3d, (int)new_x, (int)cub3d->player_y) != '1')
                cub3d->player_x = new_x;
            if (get_map_char(cub3d, (int)cub3d->player_x, (int)new_y) != '1')
                cub3d->player_y = new_y;
        }
        else if (keydata.key == MLX_KEY_RIGHT)
        {
            float old_dir_x = cub3d->dir_x;
            cub3d->dir_x = cub3d->dir_x * cos(rot_speed) - cub3d->dir_y * sin(rot_speed);
            cub3d->dir_y = old_dir_x * sin(rot_speed) + cub3d->dir_y * cos(rot_speed);
            float old_plane_x = cub3d->plane_x;
            cub3d->plane_x = cub3d->plane_x * cos(rot_speed) - cub3d->plane_y * sin(rot_speed);
            cub3d->plane_y = old_plane_x * sin(rot_speed) + cub3d->plane_y * cos(rot_speed);
        }
        else if (keydata.key == MLX_KEY_LEFT)
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

    memset(cub3d->img->pixels, 0, cub3d->img->width * cub3d->img->height * sizeof(uint32_t));
    start_dda(cub3d);
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
    mlx_delete_image(cub3d->mlx, cub3d->img);
    mlx_terminate(cub3d->mlx);
    return (0);
}
