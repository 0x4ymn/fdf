/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassih <anassih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 23:35:20 by anassih           #+#    #+#             */
/*   Updated: 2025/02/04 15:49:43 by anassih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	close_window(void *param)
{
	t_fdf	*fdf;
	int		i;

	fdf = (t_fdf *)param;
	if (fdf->map)
	{
		i = 0;
		while (i < fdf->height)
		{
			free(fdf->map[i]);
			i++;
		}
		free(fdf->map);
	}
	mlx_destroy_image(fdf->mlx, fdf->img);
	mlx_destroy_window(fdf->mlx, fdf->win);
	mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	exit(0);
	return (0);
}

int	handle_key(int key, t_fdf *fdf)
{
	if (key == 65307)
		close_window(fdf);
	return (0);
}

int	initialize_fdf(t_fdf *fdf, char *filename)
{
	ft_bzero(fdf, sizeof(t_fdf));
	fdf->z_scale = 4;
	fdf->isometric_angle = 0.55;
	if (read_file(fdf, filename) != 0)
	{
		perror("Error reading the file.");
		return (1);
	}
	if (process_map(fdf) != 0)
		return (1);
	if (set_mlx_window(fdf) != 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
	{
		perror("Usage: ./fdf <filename>");
		return (1);
	}
	if (initialize_fdf(&fdf, argv[1]) != 0)
		return (1);
	mlx_hook(fdf.win, 17, 0, close_window, &fdf);
	mlx_key_hook(fdf.win, handle_key, &fdf);
	mlx_loop(fdf.mlx);
	close_window(&fdf);
	return (0);
}
