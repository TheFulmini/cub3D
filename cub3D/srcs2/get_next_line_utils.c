/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:54:49 by amilis            #+#    #+#             */
/*   Updated: 2021/04/22 17:18:22 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

unsigned long	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*trunc_str_wfree(char *str)
{
	char	*new_str;
	int		i;

	i = 0;
	while (str[i] != '\n')
		i++;
	new_str = malloc(sizeof(char) * (i + 1));
	if (!new_str)
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

void	stock_supp(const char *str, char *sup, int nb_car, int mode)
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
		while (str[i] != '\n' && i < nb_car)
			i++;
		i++;
		while (i < nb_car)
			sup[j++] = str[i++];
		sup[j] = '\0';
	}
}

char	*ft_strjoin_wfree(char *str, char *buf, int nb_car)
{
	char	*str_cat;
	int		i;
	int		j;

	if (str == NULL || buf == NULL)
		return (NULL);
	str_cat = malloc((ft_strlen(str) + nb_car + 1) * sizeof(char));
	if (!str_cat)
		return (NULL);
	i = 0;
	j = 0;
	while (str[j])
		str_cat[i++] = str[j++];
	free(str);
	j = 0;
	while (j < nb_car && buf[j] != '\n')
		str_cat[i++] = buf[j++];
	str_cat[i] = '\0';
	return (str_cat);
}

int	newline_in_str(char *str, int nb_car, int mode)
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
		while (i < nb_car)
		{
			if (str[i] == '\n')
				return (1);
			i++;
		}
	}
	return (0);
}
