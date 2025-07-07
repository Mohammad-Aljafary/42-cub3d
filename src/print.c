# include <cub3D.h>

void print_map(t_map *map)
{
    t_map *current = map;


    printf("Map:\n");
    while (current)
    {
        ft_putstr_fd(current->data, STDOUT_FILENO);
        ft_putchar_fd('\n', STDOUT_FILENO);
        current = current->next;
    }
}

void print_textures(t_texture *textures)
{
    t_texture *current = textures;

    printf("Textures:\n");
    while (current)
    {
        printf("Name: %s, Path: %s, RGB: (%d, %d, %d)\n",
               current->name, current->path,
               current->red, current->green, current->blue);
        current = current->next;
    }
}

void print_cub3d(t_cub3d *cub3d)
{
    if (!cub3d)
    {
        printf("Cub3D structure is NULL.\n");
        return;
    }
    printf("Cub3D Configuration:\n");
    printf("Resolution: %dx%d\n", cub3d->map_width, cub3d->map_height);
    printf("Player Position: (%f, %f)\n", cub3d->player_x, cub3d->player_y);
    printf("Player Direction: %f\n", cub3d->player_angle);

    print_map(cub3d->map);
    print_textures(cub3d->textures);
}
