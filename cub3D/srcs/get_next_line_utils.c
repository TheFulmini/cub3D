/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:19:33 by afulmini          #+#    #+#             */
/*   Updated: 2021/04/22 17:18:22 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

unsigned long	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while(str[len])
		len++;
	return (len);
}

char	*truncate_str_free(char *str)
{
	char	*new_str;
	int		i;

	i = 0;
	while (str[i] != '\n')
		i++;
	if (!(new_str = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (str[i] != '\n')
	{
		new_str[i] = str[i];
		i++;
	}
	free(str);
	new_str[i] = '\0';
	return (new_str);
}

void	stock_supp(const char *str, char *sup, int nb_char, int mode)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (mode == 0)
	{
		while (str[i] != '\n' && str[i])
			i++;
		i++;
		while (str[i])
			sup[j++] = str[i++];
		sup[j] = '\0';
	}
	if (mode == 1)
	{
		while (str[i] != '\n' && i < nb_char)
			i++;
		i++;
		while (i < nb_char)
			sup[j++] = str[i++];
		sup[j] = '\0';
	}
}

char	*ft_strjoin_free(char *str, char *buffer, int nb_char)
{
	char	*str_cat;
	int		i;
	int		j;

	if (str == NULL || buffer == NULL)
		return (NULL);
	if (!(str_cat = malloc(sizeof(char) * (ft_strlen(str) + nb_char + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (str[j])
		str_cat[i++] = str[j++];
	free(str);
	j = 0;
	while (j < nb_char && buffer[j] != '\n')
		str_cat[i++] = buffer[j++];
	str_cat[i] = '\0';
	return (str_cat);
}

int		newline_in_str(char *str, int nb_char, int mode)
{
	int	i;

	i = 0;
	if (mode == 0)
	{
		while (str[i])
		{
			if (str[i] == '\n')
				return (1);
			i++;
		}
	}
	if (mode == 1)
	{
		while (i < nb_char)
		{
			if (str[i] == '\n')
				return (1);
			i++;
		}			
	}
	return (0);
}