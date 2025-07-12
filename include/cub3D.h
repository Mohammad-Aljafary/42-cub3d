/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:33:20 by yaman-alrif       #+#    #+#             */
/*   Updated: 2025/07/12 17:05:26 by malja-fa         ###   ########.fr       */
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

# include "../libft/includes/get_next_line.h"


#define PI 3.14159265358979323846

typedef struct s_map 
{
    char *data;
    int row_num;
    struct s_map *next;
    struct s_map *prev;
} t_map;

typedef struct s_tex_help
{
    int				tex_x;
	int				tex_y;
	int				y;
	double			step;
	double			tex_pos;
	unsigned char	*pixel;
	int				color;
} t_tex_help;

typedef struct s_dda
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
    int line_height;
    int draw_start;
    int draw_end;
}   t_dda;

typedef struct s_texture
{
    char *name;
    char *path;
    char **tokens;
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

typedef struct s_check
{
    int no_count;
    int so_count;
    int we_count;
    int ea_count;
    int color_count;
}   t_check;

int check_extension(const char *filename, const char *extension);
int check_dir_text(char **tokens, t_cub3d *cub3d);
int check_color(char **tokens, t_cub3d *cub3d);
int is_all_text_exist(t_cub3d *cub3d);
int read_file(int fd, t_cub3d *cub3d);
t_texture *create_node_texture(char *name, char *path, char **tokens, int red, int green, int blue);
void add_node_texture(t_texture **head, t_texture *new_node);
t_map *new_map_node (char *line, int row_num);
void add_node_map(t_map **head, t_map *new_node);
void free_map(t_map *head);
void free_textures(t_texture *head);
int process_input(char *line, t_cub3d *cub3d);
int read_texture(int fd, t_cub3d *cub3d);
int valid_file(int argc, char **argv, t_cub3d *cub3d);
void print_map(t_map *map);
void print_textures(t_texture *textures);
void print_cub3d(t_cub3d *cub3d);
int border_map(char *line);
int read_map(int fd, t_cub3d *cub3d);
void    free_cub3d(t_cub3d *cub3d);
int open_textures(t_cub3d *cub3d);
int check_map(t_cub3d *cub3d);
void start_dda(t_cub3d *cub3d);
t_texture *get_name_texture(t_texture *textures, char *name);
void	key_hook(void *param);
void	rotate(float old_dir_x, float old_plane_x, float rot_speed, t_cub3d *cub3d);
void	render_loop(void *param);
void del_new_line(char **str);
void    free_lines(int fd);
int element_exist(char *line, int index);
void fill_spaces (t_map *map);
int valid_border(t_map *map);
int is_invalid_border_char(char c);
void	move(float new_x, float new_y, t_cub3d *cub3d);
void	init_ray(t_dda *dda, t_cub3d *cub3d);
void	start_drawing(t_cub3d *cub3d, t_dda *dda);
void	find_it(t_dda *dda, t_cub3d *cub3d);
char	get_map_char(t_cub3d *cub3d, int x, int y);
#endif