/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 19:45:06 by afulmini          #+#    #+#             */
/*   Updated: 2021/03/01 17:19:31 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		has_newline(char *str)
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
	if (!s)
		return (0);
	while (s[strlen] && s[strlen] != '\n')
		strlen++;
	if (!(str = malloc(sizeof(char) * (strlen + 1))))
		return (0);
	str[strlen] = '\0';
	while (--strlen >= 0)
	{
		str[strlen] = s[strlen];
	}
	return (str);
}

char	*trim_before_newline(char *s)
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
	static char	*read_line;
	int			result;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 ||
		!(buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	result = 1;
	while (!has_newline(read_line) && result != 0)
	{
		if ((result = read(fd, buffer, BUFFER_SIZE)) == -1)
		{
			free(buffer);
			return (-1);
		}
		buffer[result] = '\0';
		read_line = ft_strjoin(read_line, buffer);
	}
	free(buffer);
	*line = trim_after_newline(read_line);
	read_line = trim_before_newline(read_line);
	if (result == 0)
		return (0);
	return (1);
}
