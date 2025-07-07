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
    int player_x;
    int player_y;
    int map_width;
    int map_height;
    float player_angle;
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
void print_map(t_map *map);
void print_textures(t_texture *textures);
void print_cub3d(t_cub3d *cub3d);
int border_map(char *line);
int read_map(int fd, t_cub3d *cub3d);

#endif