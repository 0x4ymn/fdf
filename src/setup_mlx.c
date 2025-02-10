/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassih <anassih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 23:34:56 by anassih           #+#    #+#             */
/*   Updated: 2025/01/31 18:20:27 by anassih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	isometric(int *x, int *y, int z_scaled, double angle)
{
	double	cos_angle;
	double	sin_angle;
	int		prev_x;
	int		prev_y;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	prev_x = *x;
	prev_y = *y;
	*x = (int)((prev_x - prev_y) * cos_angle);
	*y = (int)((prev_x + prev_y) * sin_angle - z_scaled);
}

static void	adjust_coordinates(t_fdf *fdf, int *x, int *y)
{
	*x += fdf->win_width / 2;
	*y += fdf->win_height / 2;
}

static void	find_z_min_max(t_fdf *fdf, int *z_min, int *z_max)
{
	int	i;
	int	j;

	i = 0;
	*z_min = fdf->map[0][0].z;
	*z_max = fdf->map[0][0].z;
	while (i < fdf->height)
	{
		j = 0;
		while (j < fdf->width)
		{
			if (fdf->map[i][j].z < *z_min)
				*z_min = fdf->map[i][j].z;
			if (fdf->map[i][j].z > *z_max)
				*z_max = fdf->map[i][j].z;
			j++;
		}
		i++;
	}
}

static void	transform_and_draw(t_fdf *fdf, int z_min, int z_max)
{
	t_transform	transform;

	transform.scale_x = (float)fdf->win_width / (fdf->width * 2);
	transform.scale_y = (float)fdf->win_height / (fdf->height * 2);
	transform.x_offset = (fdf->width - 1) * transform.scale_x / 2;
	transform.y_offset = (fdf->height - 1) * transform.scale_y / 2;
	transform.i = 0;
	while (transform.i < fdf->height)
	{
		transform.j = 0;
		while (transform.j < fdf->width)
		{
			transform.z_scaled = fdf->map[transform.i][transform.j].z;
			transform.x = transform.j * transform.scale_x - transform.x_offset;
			transform.y = transform.i * transform.scale_y - transform.y_offset;
			transform.z_scaled *= fdf->z_scale;
			isometric(&transform.x, &transform.y,
				transform.z_scaled, fdf->isometric_angle);
			adjust_coordinates(fdf, &transform.x, &transform.y);
			fdf->map[transform.i][transform.j].x = transform.x;
			fdf->map[transform.i][transform.j].y = transform.y;
			fdf->map[transform.i][transform.j].color
				= get_color(fdf->map[transform.i][transform.j].z, z_min, z_max);
			transform.j++;
		}
		transform.i++;
	}
	draw_lines(fdf);
}

static int	draw_map(t_fdf *fdf)
{
	int	z_min;
	int	z_max;

	find_z_min_max(fdf, &z_min, &z_max);
	transform_and_draw(fdf, z_min, z_max);
	return (0);
}

int	initialize_mlx(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		return (1);
	if (fdf->win_width <= 0)
		fdf->win_width = WIN_WIDTH;
	if (fdf->win_height <= 0)
		fdf->win_height = WIN_HEIGHT;
	fdf->win = mlx_new_window(fdf->mlx, fdf->win_width, fdf->win_height, "FDF");
	if (!fdf->win)
		return (1);
	fdf->img = mlx_new_image(fdf->mlx, fdf->win_width, fdf->win_height);
	if (!fdf->img)
	{
		mlx_destroy_window(fdf->mlx, fdf->win);
		return (1);
	}
	fdf->data_addr = mlx_get_data_addr(fdf->img, &fdf->bpp, &fdf->size_line,
			&fdf->endian);
	if (!fdf->data_addr)
	{
		mlx_destroy_image(fdf->mlx, fdf->img);
		mlx_destroy_window(fdf->mlx, fdf->win);
		return (1);
	}
	return (0);
}

int	render_image_to_window(t_fdf *fdf)
{
	if (draw_map(fdf) != 0)
		return (1);
	if (mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0) == -1)
		return (1);
	return (0);
}

int	set_mlx_window(t_fdf *fdf)
{
	if (initialize_mlx(fdf) != 0)
		return (1);
	if (render_image_to_window(fdf) != 0)
		return (1);
	return (0);
}