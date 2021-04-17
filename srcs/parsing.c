/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 14:42:52 by afulmini          #+#    #+#             */
/*   Updated: 2021/04/17 16:29:50 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		ft_parse_map(char *file, t_recup *recup)
{
	int		fd;
	int		ret;
	char	*str;

	ret = 1;
	str = NULL;
	fd = open(file, O_RDONLY);
	if (!(recup->map = malloc(sizeof(char*) * recup->nblines)))
		return (0);
	while (ret != 0)
	{
		ret = get_next_line(fd, &str);
		if (ft_is_map(str) == 1)
			ft_copy_map(str, recup);
		free(str);
	}
	close(fd);
	ft_init_sprite(recup);
	ft_mlx(recup);
	return (0);
}

void	ft_parse(char *file, t_recup *recup)
{
	int		fd;
	int		ret;
	char	*str;

	ret = 1;
	str = NULL;
	ft_init(recup);
	fd = open(file, O_RDONLY);
	while (ret != 0)
	{
		ret = get_next_line(fd, &str);
		ft_color_resolution(&str, recup);
		ft_texture(str, recup);
		ft_map(str, recup);
		free(str);
	}
	close(fd);
	if (recup->sizelines == 0 || recup->nblines == 0)
		ft_error(recup, "Absent Map\n");
	ft_parse_map(file, recup);
}

int		ft_check_cub(char *str, t_recup *recup)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	while (str[i] != '.')
	{
		i--;
		if (i == 0)
		{
			ft_error(recup, "Invalid map name\n");
			return (0);
		}
	}
	if (str[i + 1] == 'c' && str[i + 2] == 'u' && str[i + 3] == 'b')
		ft_parse(str, recup);
	else
		ft_error(recup, "Invalid map name\n");
	return (0);
}

int		main(int argc, char **argv)
{
	t_recup		recup;
	recup.save = 0;

	if (argc == 2 || argc == 3)
	{
		if (argc == 3)
			recup.save = 1;
		ft_check_cub(argv[1], &recup);
	}
	else
		write(1, "Error\n Wrong number of arguments.\nPlease enter 2 or 3 arguments maximum\n", 75);
}
