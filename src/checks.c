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

int border_map(char *line)
{
    size_t len; 
    size_t i;

    len = ft_strlen(line);
    i = 1;
    if (len < 3)
        return (0);
    while (i < len - 1)
    {
        if (line[i] != '1' && line[i] != '0' && line[i] != ' ')
            return (0);
        i++;
    }
    return (1);
}

int process_input(char *line, t_cub3d *cub3d)
{
    char *line_trimmed;
    char **tokens;
    t_map *new_map;
    char *dup_line;
    int result;

    new_map = NULL;
    dup_line = NULL;
    line_trimmed = ft_strtrim(line, " \t\n\r");
    if (!line_trimmed)
        return (-1);
    if (line_trimmed[0] == '\0')
    {
        free(line_trimmed);
        return (0);
    }
    tokens = ft_split(line_trimmed, ' ');
    free(line_trimmed);
    if (!tokens)
        return (-1);
    result = check_dir_text(tokens, cub3d);
    if (result == -1)
        return (-1);
    else if (result)
        return (0);
    result = check_color(tokens, cub3d);
    if (result == -1)
        return (-1);
    else if (result == 1)
        return (0);
    ft_free_split(tokens);
    result = border_map (line);
    if (!result)
    {
        ft_fprintf(2, "Error: Invalid Texture\n");
        return (-1);
    }
    else
    {
        dup_line = ft_strdup(line);
        if (!dup_line)
            return (-1);
        new_map = new_map_node(dup_line, 1);
        if (!new_map)
            return (-1);
        add_node_map(&cub3d->map, new_map);
        return (2);
    }
    return (0);
}

void del_new_line(char **str)
{
    int len;

    if (!str || !*str)
        return ;
    len = ft_strlen(*str);
    if (len > 0 && (*str)[len - 1] == '\n')
        (*str)[len - 1] = '\0';
}

void    free_lines(int fd)
{
    char    *line;

    line = get_next_line(fd);
    while(line)
    {
        free (line);
        line = get_next_line(fd);
    }
}

int read_texture(int fd, t_cub3d *cub3d)
{
    char *line;
    int result;

    line = get_next_line(fd);
    while (line)
    {
        del_new_line(&line);
        result = process_input(line, cub3d);
        free (line);
        if (result == -1)
            return (-1);
        else if (result == 2)
            break;
        line = get_next_line(fd);
    }
    return (0);
}

int read_map (int fd, t_cub3d *cub3d)
{
    char *line;
    t_map *new_map;
    int i;

    line = get_next_line(fd);
    i = 2;
    while (line)
    {
        del_new_line(&line);
        if (line[0] == '\0')
        {
            free(line);
            return (-1);
        }
        if (ft_strcmp(line, "\n") == 0 || ft_strcmp(line, "\r\n") == 0)
        {
            free(line);
            return (-1);
        }
        new_map = new_map_node(line, i);
        if (!new_map)
        {
            free(line);
            return (-1);
        }
        add_node_map(&cub3d->map, new_map);
        line = get_next_line(fd);
        i++;
    }
    if (cub3d->map == NULL)
    {
        free(line);
        return (-1);
    }
    return (0);   
}

int read_file(int fd, t_cub3d *cub3d)
{
    if (read_texture(fd, cub3d) == -1)
    {
        free_lines(fd);
        return (-1);
    }
    if (read_map(fd, cub3d) == -1)
    {
        free_lines(fd);
        return (-1);
    }
    if (is_all_text_exist(cub3d) == -1)
        return (-1);
   /*  if (open_textures(cub3d) == -1)
        return (-1); */
    if (check_map(cub3d) == -1)
        return (-1);
    print_cub3d(cub3d);
    return (0);
}
