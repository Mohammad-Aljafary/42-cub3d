# include <cub3D.h>

int check_extension(const char *filename, const char *extension)
{
    size_t filename_len = ft_strlen(filename);
    size_t extension_len = ft_strlen(extension);

    if (filename_len < extension_len)
        return (-1);
    if (ft_strcmp(filename + filename_len - extension_len, extension) != 0)
        return (-1);
    return (0);
}

int process_input(char *line, t_cub3d *cub3d)
{
    char *line_trimmed;
    char **tokens;

    line_trimmed = ft_strtrim(line, " \t\n\r");
    if (!line_trimmed)
        return (-1);
    if (line_trimmed[0] == '\0')
        return (0);
    tokens = ft_split(line_trimmed, ' ');
    free(line_trimmed);
    if (!tokens)
        return (-1);
    if (ft_strcmp(tokens[0], "NO") == 0 || ft_strcmp(tokens[0], "SO") == 0 ||
        ft_strcmp(tokens[0], "WE") == 0 || ft_strcmp(tokens[0], "EA") == 0)
    {
        if (tokens[1] && tokens[2] == NULL)
        {
            t_texture *new_texture = create_node_texture(tokens[0], tokens[1], -1, -1, -1);
            if (!new_texture)
            {
                free(tokens);
                return (-1);
            }
            new_texture->next = cub3d->textures;
            cub3d->textures = new_texture;
        }
        else
        {
            free(tokens);
            return (-1);
        }
    }
    else if (ft_strcmp(tokens[0], "F") == 0 || ft_strcmp(tokens[0], "C") == 0)
    {
        if (tokens[1] && tokens[2] && tokens[3] == NULL)
        {
            int red = ft_atoi(tokens[1]);
            int green = ft_atoi(tokens[2]);
            int blue = ft_atoi(tokens[3]);
            if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
            {
                ft_free_split(tokens);
                return (-1);
            }
            t_texture *new_texture = create_node_texture(tokens[0], NULL, red, green, blue);
            if (!new_texture)
            {
                ft_free_split(tokens);
                return (-1);
            }
            add_node_texture(&cub3d->textures, new_texture);
        }
        else
        {
            ft_free_split(tokens);
            return (-1);
        }
    }
    else if (!border_map (line))
    {
        ft_free_split(tokens);
        return (-1);
    }
    else
    {
        t_map *new_map = new_map_node(line);
        if (!new_map)
        {
            ft_free_split(tokens);
            return (-1);
        }
        add_map_node(&cub3d->map, new_map);
        return (2);
    }
    return (0);
}

int read_texture(int fd, t_cub3d *cub3d)
{
    char *line;

    line = get_next_line(fd);
    while (line)
    {
        if (process_input(line, cub3d) == -1)
        {
            free(line);
            return (-1);
        }
        free (line);
        line = get_next_line(fd);
    }
    return (0);
}

int read_file(int fd, t_cub3d *cub3d)
{
    char *line;

    if (read_texture(fd, cub3d) == -1)
        return (-1);
    if (read_map(fd, cub3d) == -1)
        return (-1);
}
