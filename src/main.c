#include <cub3D.h>

int main()
{
    t_cub3d *cub3d;
    cub3d = malloc(sizeof(t_cub3d));
    if (!cub3d)
    {
        printf("Failed to allocate memory for cub3d\n");
        return (1);
    }
    printf("Memory allocated for cub3d\n");
    ft_memset(cub3d, 0, sizeof(t_cub3d));
    cub3d->map_width = 800;
    cub3d->map_height = 600;
    cub3d->player_x = 4.5f;
    cub3d->player_y = 4.5f;
    cub3d->player_angle = 1.5708f;
    cub3d->dir_x = cos(cub3d->player_angle);
    cub3d->dir_y = sin(cub3d->player_angle);
    cub3d->plane_x = -cub3d->dir_y * 0.66f;
    cub3d->plane_y = cub3d->dir_x * 0.66f;
    cub3d->mlx = mlx_init(cub3d->map_width, cub3d->map_height, "cub3D", true);
    if (!cub3d->mlx)
    {
        printf("Failed to initialize MLX\n");
        free(cub3d);
        return (1);
    }
    cub3d->textures = NULL;
    cub3d->textures = create_node_texture("NO", "wall/wall_1.xpm", 0, 0, 0);
    if (!cub3d->textures)
    {
        printf("Failed to create texture node\n");
        mlx_terminate(cub3d->mlx);
        free(cub3d);
        return (1);
    }
    cub3d->textures->next = create_node_texture("SO", "wall/wall_3.xpm", 0, 0, 0);
    cub3d->textures->next->next = create_node_texture("WE", "wall/wall_4.xpm", 0, 0, 0);
    cub3d->textures->next->next->next = create_node_texture("EA", "wall/wood.xpm", 0, 0, 0);
    cub3d->textures->next->next->next->next = create_node_texture("F", NULL, 120, 120, 120);
    cub3d->textures->next->next->next->next->next = create_node_texture("C", NULL, 50, 50, 50);
    cub3d->textures->next->next->next->next->next->next = NULL;
    cub3d->map = NULL;
    add_node_map(&cub3d->map, create_node_map("1111111111", 0));
    add_node_map(&cub3d->map, create_node_map("1000000001", 1));
    add_node_map(&cub3d->map, create_node_map("1001111001", 2));
    add_node_map(&cub3d->map, create_node_map("1000000001", 3));
    add_node_map(&cub3d->map, create_node_map("1001111001", 4));
    add_node_map(&cub3d->map, create_node_map("1000000001", 5));
    add_node_map(&cub3d->map, create_node_map("1111111111", 6));
    
    main_1(cub3d);

    // free_map(cub3d->map);
    // free_textures(cub3d->textures);
    // free(cub3d); i will free it when finsh all the project
    return (0);
}
