/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaman-alrifai <yaman-alrifai@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:33:20 by yaman-alrif       #+#    #+#             */
/*   Updated: 2025/07/08 15:41:02 by yaman-alrif      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include <errno.h>
# include <MLX42/MLX42.h>
# include <MLX42/MLX42_Int.h>
# include <libft.h>

typedef struct s_map 
{
    char *data;
    int row_num;
    struct s_map *next;
    struct s_map *prev;
} t_map;

typedef struct s_texture
{
    char *name;
    char *path;
    xpm_t *xpm;
    mlx_texture_t *mlx_texture;
    int red;
    int green;
    int blue;
    struct s_texture *next;
} t_texture;

typedef struct s_cub3d
{
    mlx_t *mlx;
    mlx_image_t *img;
    t_map *map;
    t_texture *textures;
    int map_width;
    int map_height;
    float player_y;
    float player_x;
    float player_angle;
    float dir_x;
    float dir_y;
    float plane_x;
    float plane_y;
} t_cub3d;


int check_extension(const char *filename, const char *extension);
int read_file(int fd, t_cub3d *cub3d);
t_texture *create_node_texture(char *name, char *path, int red, int green, int blue);
t_map *create_node_map(char *line, int row_num);
void add_node_map(t_map **head, t_map *new_node);
void free_map(t_map *head);
void free_textures(t_texture *head);
int process_input(char *line, t_cub3d *cub3d);
int read_texture(int fd, t_cub3d *cub3d);
int valid_file(int argc, char **argv, t_cub3d *cub3d);
int main_1(t_cub3d *cub3d);
void start_dda(t_cub3d *cub3d, mlx_image_t *img);
#endif