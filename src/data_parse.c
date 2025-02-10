/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassih <anassih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:53:08 by anassih           #+#    #+#             */
/*   Updated: 2025/01/31 17:57:42 by anassih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int	parse_line(t_fdf *fdf, char *line, int i)
{
	int	j;
	int	width;

	fdf->split = ft_split(line, ' ');
	if (i == 0)
	{
		width = 0;
		while (fdf->split[width])
			width++;
		fdf->width = width;
	}
	fdf->map[i] = (t_map *)malloc(sizeof(t_map) * fdf->width);
	if (!fdf->map[i])
		return (1);
	j = 0;
	while (j < fdf->width)
	{
		fdf->map[i][j].z = ft_atoi(fdf->split[j]);
		fdf->map[i][j].color = 0xFFFFFF; // Default color
		free(fdf->split[j]);
		j++;
	}
	free(fdf->split);
	free(line);
	return (0);
}

static int	count_lines(t_fdf *fdf, char *filename)
{
	char	*line;

	fdf->fd = open(filename, O_RDONLY);
	if (fdf->fd < 0)
		return (1);
	fdf->height = 0;
	while ((line = get_next_line(fdf->fd)) != NULL)
	{
		fdf->height++;
		free(line);
	}
	close(fdf->fd);
	return (0);
}

int	read_file(t_fdf *fdf, char *filename)
{
	char	*line;
	int		i;

	if (count_lines(fdf, filename) != 0)
		return (1);
	fdf->map = (t_map **)malloc(sizeof(t_map *) * fdf->height);
	if (!fdf->map)
		return (1);
	fdf->fd = open(filename, O_RDONLY);
	if (fdf->fd < 0)
		return (1);
	i = 0;
	while ((line = get_next_line(fdf->fd)) != NULL)
	{
		if (parse_line(fdf, line, i) != 0)
			return (1);
		i++;
	}
	close(fdf->fd);
	return (0);
}

int	process_map(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->height)
	{
		j = 0;
		while (j < fdf->width)
		{
			fdf->map[i][j].x = j;
			fdf->map[i][j].y = i;
			j++;
		}
		i++;
	}
	return (0);
}

// Function to parse the map file and populate the fdf structure
int	parse_map(t_fdf *fdf)
{
	fdf->width = 10;
	fdf->height = 10;
	fdf->map = (t_map **)malloc(sizeof(t_map *) * fdf->height);
	if (!fdf->map)
		return (0);
	int i;

	i = 0;
	while (i < fdf->height)
	{
		fdf->map[i] = (t_map *)malloc(sizeof(t_map) * fdf->width);
		if (!fdf->map[i])
			return (0);
		int j;

		j = 0;
		while (j < fdf->width)
		{
			fdf->map[i][j].x = j;
			fdf->map[i][j].y = i;
			fdf->map[i][j].z = 0;
			fdf->map[i][j].color = 0xFFFFFF;
			j++;
		}
		i++;
	}
	return (1);
}