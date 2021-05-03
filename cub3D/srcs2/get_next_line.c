/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:54:44 by amilis            #+#    #+#             */
/*   Updated: 2021/05/03 12:25:39 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	end_or_error(int ret, char *buf, char **sup_str, char *line)
{
	if (buf)
		free(buf);
	if (line && ret != 0)
		free(line);
	if (*sup_str)
	{
		free(*sup_str);
		*sup_str = NULL;
	}
	return (ret);
}

int	alloc_strs(char **buf, char **sup, int fd)
{
	*buf = malloc((BUFFER_SIZE) * sizeof(char));
	if (!(*buf))
		return (0);
	if (sup[fd] == NULL)
	{
		sup[fd] = malloc(BUFFER_SIZE * sizeof(char));
		if (!(sup[fd]))
			return (0);
		sup[fd][0] = 0;
	}
	return (1);
}

char	*ft_strdup(const char *str)
{
	char	*str_cpy;
	int		str_len;
	int		i;

	i = 0;
	str_len = ft_strlen((char *)str);
	str_cpy = malloc((str_len + 1) * sizeof(char));
	if (str_cpy == NULL)
		return (NULL);
	while (i < str_len)
	{
		str_cpy[i] = str[i];
		i++;
	}
	str_cpy[i] = '\0';
	return (str_cpy);
}

int	make_line(int fd, char *buf, char **line, char **sup)
{
	int	ret;

	ret = read(fd, buf, BUFFER_SIZE);
	if (ret == -1 || ret == 0)
		return (end_or_error(ret, buf, &sup[fd], *line));
	while (!newline_in_str(buf, ret, 1))
	{
		*line = ft_strjoin_wfree(*line, buf, ret);
		if (!(*line))
			return (end_or_error(-1, buf, &sup[fd], *line));
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1 || ret == 0)
			return (end_or_error(ret, buf, &sup[fd], 0));
	}
	*line = ft_strjoin_wfree(*line, buf, ret);
	if (!(*line))
		return (end_or_error(-1, buf, &sup[fd], *line));
	stock_supp(buf, sup[fd], ret, 1);
	free(buf);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	char		*buf;
	static char	*sup[OPEN_MAX];
	int			ret;

	if (fd < 0 || fd > OPEN_MAX || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!(alloc_strs(&buf, sup, fd)))
		return (end_or_error(-1, buf, &sup[fd], 0));
	*line = ft_strdup(sup[fd]);
	if (!(*line))
		return (end_or_error(-1, buf, &sup[fd], 0));
	if (newline_in_str(*line, 0, 0))
	{
		stock_supp(*line, sup[fd], 0, 0);
		*line = trunc_str_wfree(*line);
		if (!(*line))
			return (end_or_error(-1, buf, &sup[fd], *line));
		free(buf);
		return (1);
	}
	ret = make_line(fd, buf, line, sup);
	return (ret);
}
