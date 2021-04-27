/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:47:52 by afulmini          #+#    #+#             */
/*   Updated: 2021/04/26 18:24:54 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	get_path_bis(t_data *d, t_parse *p, char *path)
{
	int fd;

	if (ft_strncmp(d->id, "NO") == 0)
		p->no_path = path;
	if (ft_strncmp(d->id, "SO") == 0)
		p->so_path = path;
	if (ft_strncmp(d->id, "EA") == 0)
		p->ea_path = path;
	if (ft_strncmp(d->id, "WE") == 0)
		p->we_path = path;
	if (ft_strncmp(d->id, "S") == 0)
		p->sprite_path = path;
	fd = open(path, O_WRONLY);
	if (fd < 0)
	{
		close(fd);
		error_exit("Invalid texture or sprite path.", d, p, 0);
	}
	
}

void	get_path(t_data *d, t_parse *p, t_elems *e)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	if (count_arg(d->line) != 1)
		error_exit("Invali  numbers of arguments : no path.", d, p, 0);
	while (is_space(d->line[i]) && d->line[i])
		i++;
	while (is_upper(d->line[i]) && d->line[i])
		i++;
	while (is_space(d->line[i]) && d->line[i++])
		j = i;
	while(!is_space(d->line[i]) && d->line[i])
		i++;
	if (!(path = malloc(sizeof(char) * (i - j + 1))))
		error_exit("Error. Not enough memory to allocate.", d, p, 0);
	i = j;
	j = 0;
	while (!is_space(d->line[i]) && d->line[i])
		path[j++] = d->line[i++];
	path[j] = 0;
	get_path_bis(d, p, path);
	set_bool_elem(d, e, p);
}

void	get_colour(t_data *d, t_parse *p, t_elems *e)
{
	int	r;
	int g;
	int b;
	int i;

	i = 0;
	check_color_format(d, p);
	while (!is_digit(d->line[i]))
		i++;
	r = ft_atoi(d->line + i);
	while (d->line[i] != ',')
		i++;
	i++;
	g = ft_atoi(d->line + i);
	while (d->line[i] != ',')
		i++;
	i++;
	b = ft_atoi(d->line + i);
	if (b < 0 || b > 255 || r < 0 || r > 255 || g < 0 || g > 255)
		error_exit("Parameter not in RGB range [0:255].", d, p, 0);
	if (ft_strncmp(d->id, "C") == 0)
		p->ceil_color = 65536 * r + 256 * g + b;
	if (ft_strncmp(d->id, "F") == 0)
		p->floor_color = 65536 * r + 256 * g + b;
	set_bool_elem(d, e, p);
}

void	get_element(t_data *d, t_parse *p, t_elems *e)
{
	if (ft_strncmp(d->id, "R") == 0)
		get_res(d, p, e);
	else if (ft_strncmp(d->id, "NO") == 0)
		get_path(d, p, e);
	else if (ft_strncmp(d->id, "SO") == 0)
		get_path(d, p, e);
	else if (ft_strncmp(d->id, "WE") == 0)
		get_path(d, p, e);
	else if (ft_strncmp(d->id, "EA") == 0)
		get_path(d, p, e);
	else if (ft_strncmp(d->id, "S") == 0)
		get_path(d, p, e);
	else if (ft_strncmp(d->id, "F") == 0)
		get_path(d, p, e);
	else if (ft_strncmp(d->id, "C") == 0)
		get_path(d, p, e);
	else
		error_exit("Invalid indentifier", d, p, 0)
}

void	parse_elements(t_data *d, t_parse *p)
{
	int		ret;
	t_elems	e;
	int		i;

	init_elems(&e);
	ret = 1;
	i = 1;
	while (ret > 0 && !all_elements_found(e))
	{
		ret = get_next_line(d->fd, &d->line);
		if (ret = -1)
			error_exit("Could not read file.", d, 0, 0);
		if (!is_empty(d->line) || (is_upper(d->line[0])))
		{
			d->id = get_identifier(d);
			get_element(d, p, &e);
			if (d->id)
				free(d->id);
		}
		if (d->line)
			free(d->line);
	}
}