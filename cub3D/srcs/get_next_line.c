/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:36:14 by afulmini          #+#    #+#             */
/*   Updated: 2021/04/27 16:14:55 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		end_or_error(int ret, char *buffer, char **sup_str, char *line)
{
	if (buffer)
		free(buffer);
	if (line && ret != 0)
		free(line);
	if (*sup_str)
	{
		free(*sup_str);
		*sup_str = NULL;
	}
	return (ret);
}

int		malloc_str(char **buffer, char **supp, int fd)
{
	if (!(buffer = malloc(sizeof(char) * (BUFFER_SIZE))))
		return (0);
	if (supp[fd] == NULL)
	{
		if (!(supp[fd] = malloc(sizeof(char) * BUFFER_SIZE)))
			return (0);
		supp[fd][0] = 0;
	}
	return (1);
}

char	*ft_strdup(const char *str)
{
	char	*str_cpy;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen((char *)str);
	if (!(str_cpy = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i++ < len)
		str_cpy[i] = str[i];
	str_cpy[i] = '\0';
	return (str_cpy);
}

int		make_line(int fd, char *buffer, char **line, char **supp)
{
	int	ret;

	ret = read(fd, buffer, BUFFER_SIZE);
	if (ret == -1 || ret == 0)
		return (end_or_error(ret, buffer, &supp[fd], *line));
	while (!newline_in_str(buffer, ret, 1))
	{
		*line = ft_strjoin_free(*line, buffer, ret);
		if (!(*line))
			return (end_or_error(-1, buffer, &supp[fd], *line));
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret == -1 || ret == 0)
			return (end_or_error(ret, buffer, &supp[fd], *line));
	}
	*line = ft_strjoin_free(*line, buffer, ret);
	if (!(*line))
		return (end_or_error(-1, buffer, &supp[fd], *line));
	stock_supp(buffer, supp[fd], ret, 1);
	free(buffer);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	char		*buffer;
	static char	*supp[OPEN_MAX];
	int			ret;

	if (fd < 0 || fd > OPEN_MAX || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!(malloc_str(&buffer, supp, fd)))
		return (end_or_error(-1, buffer, &supp[fd], 0));
	*line = ft_strdup(supp[fd]);
	if (!(*line))
		return (end_or_error(-1, buffer, &supp[fd], 0));
	if (newline_in_str(*line, 0, 0))
	{
		stock_supp(*line, supp[fd], 0, 0);
		*line = truncate_str_free(*line);
		if (!(*line))
			return (end_or_error(-1, buffer, &supp[fd], *line));
		free(buffer);
		return (ret);
	}
	ret = make_line(fd, buffer, line, supp);
	return (ret);
}
