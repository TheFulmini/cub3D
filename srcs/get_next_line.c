/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:36:14 by afulmini          #+#    #+#             */
/*   Updated: 2021/05/03 12:25:39 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	end_or_error(int ret, char *buffer, char **sup_str, char *line)
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

int	malloc_str(char **buffer, char **supp, int fd)
{
	*buffer = malloc((BUFFER_SIZE) * sizeof(char));
	if (!(*buffer))
		return (0);
	if (supp[fd] == NULL)
	{
		supp[fd] = malloc((BUFFER_SIZE) * sizeof(char));
		if (!(supp[fd]))
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
	str_cpy = malloc(sizeof(char) * (len + 1));
	if (str_cpy == NULL)
		return (NULL);
	while (i < len)
	{
		str_cpy[i] = str[i];
		i++;
	}
	str_cpy[i] = '\0';
	return (str_cpy);
}

int	make_line(int fd, char *buffer, char **line, char **supp)
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
			return (end_or_error(ret, buffer, &supp[fd], 0));
	}
	*line = ft_strjoin_free(*line, buffer, ret);
	if (!(*line))
		return (end_or_error(-1, buffer, &supp[fd], *line));
	stock_supp(buffer, supp[fd], ret, 1);
	free(buffer);
	return (1);
}

int	get_next_line(int fd, char **line)
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
		return (1);
	}
	ret = make_line(fd, buffer, line, supp);
	return (ret);
}
