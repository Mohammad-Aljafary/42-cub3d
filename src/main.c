#include <cub3D.h>



int main()
{
    t_cub3d *cub3d;

    cub3d = malloc(sizeof(t_cub3d));
    ft_memset(cub3d, 0, sizeof(t_cub3d));

    cub3d->map_width = 800;
    cub3d->map_height = 600;
    cub3d->player_x = 400;
    cub3d->player_y = 300;
    cub3d->player_angle = 0.0f;
    cub3d->map = NULL;
    main_1(cub3d);
    
    free(cub3d);
    return (0);
}
