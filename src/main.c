#include <cub3D.h>

int     valid_file(int argc, char** argv, t_cub3d *cub3d)
{
    int fd;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
        return (-1);
    }
    if (check_extension(argv[1], ".cub") == -1)
    {
        fprintf(stderr, "Error: Invalid file extension. Expected .cub file.\n");
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
        fprintf(stderr, "Error reading file.\n");
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
        free(cub3d);
        fprintf(stderr, "Error: Invalid file or arguments.\n");
        return (EXIT_FAILURE);
    }
    free_textures(cub3d->textures);
    free (cub3d);
}
