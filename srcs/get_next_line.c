/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 16:47:03 by afulmini          #+#    #+#             */
/*   Updated: 2021/04/17 16:51:18 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		has_new_line(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

char	*trim_after_newline(char *s)
{
	char	*str;
	int		strlen;

	strlen = 0;
	if (!str)
		return (0);
	while (s[strlen] && s[strlen] != '\n')
		strlen++;
	if (!(str = malloc(sizeof(char) * (strlen + 1))))
		return (0);
	str[strlen] = '\0';
	while (strlen-- >= 0)
		str[strlen] = s[strlen];
	return (str);
}

char	*trim_before_line(char *s)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free(s);
		return (0);
	}
	if (!(str = malloc(sizeof(char) * ((ft_strlen(s) - i) + 1))))
		return (0);
	i++;
	while (s[i])
		str[j++] = s[i++];
	str[j] = '\0';
	free(s);
	return (str);
}

int		get_next_line(int fd, char **line)
{
	char		*buffer;
	static char	*arr_read_line[OPEN_MAX];
	int			r;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || fd >= OPEN_MAX ||
		!(buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	r = 1;
	while (!has_new_line(arr_read_line[fd]) && r != 0)
	{
		if ((r = read(fd, buffer, BUFFER_SIZE)) == -1)
		{
			free(buffer);
			return (-1);
		}
		buffer[r] = '\0';
		arr_read_line[fd] = ft_strjion(arr_read_line[fd], buffer);
	}
	free(buffer);
	*line = trim_after_new_line(arr_read_line[fd]);
	arr_read_line[fd] = trim_before_new_line(arr_read_line[fd]);
	if (r == 0)
		return (0);
	return (1);
}
