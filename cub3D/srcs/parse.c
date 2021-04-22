/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:59:07 by afulmini          #+#    #+#             */
/*   Updated: 2021/04/22 17:21:36 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_parser(t_parse *pars)
{
	int	i;

	if (pars)
	{
		if (pars->no_path)
			free(pars->no_path);
		if (pars->so_path)
			free(pars->so_path);
		if (pars->ea_path)
			free(pars->ea_path);
		if (pars->we_path)
			free(pars->we_path);
		if (pars->sprite_path)
			free(pars->sprite_path);
		if (pars->sprite_tab)
			free(pars->sprite_tab);
		i = 0;
		if (pars->map)
		{
			while (pars->map[i])
				free(pars->map[i++]);
			free(pars->map);
		}
	}
}

void	error_exit(char *error_msg, t_data *d, t_parse *pars, char **map)
{
	int	i;

	if (d)
	{
		if (d->id)
			free(d->id);
		if(d->line)
			free(d->line);
		if (d->fd)
			close(d->fd);
	}
	if (pars)
		free_parser(pars);
	i = 0;
	if (map)
		while (map[i])
			free(map[i++]);
		free(map);
	if (error_msg))
	{
		printf("ERROR\n%s\n", error_msg);
		exit(0);
	}
}

void	check_map(t_data *d, t_parse *pars)
{
	d->line = NULL;
	d->id = NULL;
	while (is_)
}