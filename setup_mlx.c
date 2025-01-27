/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassih <anassih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 23:34:56 by anassih           #+#    #+#             */
/*   Updated: 2025/01/25 23:34:56 by anassih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	put_pixel(t_fdf *fdf, int x, int y, int color)
{
    if (x >= 0 && x < fdf->win_width && y >= 0 && y < fdf->win_height)
    {
        int pixel_pos = (y * fdf->size_line) + (x * (fdf->bpp / 8));
        *((unsigned int *)(fdf->data_addr + pixel_pos)) = color;
    }
}

static void	isometric(int *x, int *y, int z, int z_scale, double angle)
{
    const double cos_angle = cos(angle);
    const double sin_angle = sin(angle);
    int prev_x = *x;
    int prev_y = *y;
    z *= z_scale;
    *x = (int)((prev_x - prev_y) * cos_angle);
    *y = (int)((prev_x + prev_y) * sin_angle - z);
}

static void	adjust_coordinates(t_fdf *fdf, int *x, int *y)
{
    *x += fdf->win_width / 2;
    *y += fdf->win_height / 2;
}

static void	find_z_min_max(t_fdf *fdf, int *z_min, int *z_max)
{
    int i = 0;
    int j;

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
    int i = 0;
    int j;
    float scale_x = (float)fdf->win_width / (fdf->width * 2);
    float scale_y = (float)fdf->win_height / (fdf->height * 2);
    int x_offset = (fdf->width - 1) * scale_x / 2;
    int y_offset = (fdf->height - 1) * scale_y / 2;

    while (i < fdf->height)
    {
        j = 0;
        while (j < fdf->width)
        {
            int x = j * scale_x - x_offset;
            int y = i * scale_y - y_offset;
            int z_scaled = fdf->map[i][j].z;
            isometric(&x, &y, z_scaled, fdf->z_scale, fdf->isometric_angle);
            adjust_coordinates(fdf, &x, &y);
            fdf->map[i][j].x = x;
            fdf->map[i][j].y = y;
            fdf->map[i][j].color = get_color(fdf->map[i][j].z, z_min, z_max);
            j++;
        }
        i++;
    }
    draw_lines(fdf);
}

static int	draw_map(t_fdf *fdf)
{
    int z_min, z_max;
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
        return (1);
    fdf->data_addr = mlx_get_data_addr(fdf->img, &fdf->bpp, &fdf->size_line, &fdf->endian);
    if (!fdf->data_addr)
        return (1);
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