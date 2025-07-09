#include <cub3D.h>

int     valid_file(int argc, char** argv, t_cub3d *cub3d)
{
    int fd;

    if (argc != 2)
    {
        ft_fprintf(2, "Usage: %s <map_file>\n", argv[0]);
        return (-1);
    }
    if (check_extension(argv[1], ".cub") == -1)
    {
        ft_fprintf(2, "Error: Invalid file extension. Expected .cub file.\n");
        return (-1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (-1);
    }
    if (read_file(fd, cub3d) == -1)
    {
        close(fd);
        return (-1);
    }
    close(fd);
    return (0);
}

int main(int argc, char** argv)
{
    t_cub3d *cub3d;

    cub3d = malloc(sizeof(t_cub3d));
    ft_memset(cub3d, 0, sizeof(t_cub3d));
    if (valid_file(argc, argv, cub3d) == -1)
    {
        free_cub3d(cub3d);
        return (EXIT_FAILURE);
    }
    free_cub3d(cub3d);
}
