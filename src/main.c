#include <cub3D.h>



int main()
{
    t_cub3d *cub3d;

    cub3d = malloc(sizeof(t_cub3d));
    ft_memset(cub3d, 0, sizeof(t_cub3d));

    cub3d->map_width = 800;
    cub3d->map_height = 600;
    cub3d->player_x = 4;
    cub3d->player_y = 4;
    cub3d->player_angle = 90.0f;

    cub3d->textures = NULL;
    cub3d->textures = create_node_texture("NO", "wall/wall_1.xpm", 0, 0, 0);
    cub3d->textures->next = create_node_texture("SO", "wall/wall_3.xpm", 0, 0, 0);
    cub3d->textures->next->next = create_node_texture("WE", "wall/wall_4.xpm", 0, 0, 0);
    cub3d->textures->next->next->next = create_node_texture("EA", "wall/wood.xpm", 0, 0, 0);
    cub3d->textures->next->next->next->next = create_node_texture("F", NULL, 120, 120, 120);
    cub3d->textures->next->next->next->next->next = create_node_texture("C", NULL, 50, 50, 50);

    cub3d->map = NULL;
    add_node_map(&cub3d->map, create_node_map("1111111111", 0));
    add_node_map(&cub3d->map, create_node_map("1000000001", 1));
    add_node_map(&cub3d->map, create_node_map("1000000001", 2));
    add_node_map(&cub3d->map, create_node_map("1000W00001", 3));
    add_node_map(&cub3d->map, create_node_map("1000000001", 4));
    add_node_map(&cub3d->map, create_node_map("1000000001", 5));
    add_node_map(&cub3d->map, create_node_map("1111111111", 6));
    
    main_1(cub3d);

    free_map(cub3d->map);
    free_textures(cub3d->textures);
    free(cub3d);
    return (0);
}
