/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassih <anassih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 00:09:06 by anassih           #+#    #+#             */
/*   Updated: 2025/01/26 00:09:06 by anassih          ###   ########.fr       */
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

static void	draw_line(t_fdf *fdf, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx, sy;
    int err = dx - dy;

    if (x0 < x1)
        sx = 1;
    else
        sx = -1;

    if (y0 < y1)
        sy = 1;
    else
        sy = -1;

    while (1)
    {
        put_pixel(fdf, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = err * 2;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void	draw_lines(t_fdf *fdf)
{
    int i, j;

    for (i = 0; i < fdf->height; i++)
    {
        for (j = 0; j < fdf->width; j++)
        {
            if (j < fdf->width - 1)
                draw_line(fdf, fdf->map[i][j].x, fdf->map[i][j].y, fdf->map[i][j + 1].x, fdf->map[i][j + 1].y, fdf->map[i][j].color);
            if (i < fdf->height - 1)
                draw_line(fdf, fdf->map[i][j].x, fdf->map[i][j].y, fdf->map[i + 1][j].x, fdf->map[i + 1][j].y, fdf->map[i][j].color);
        }
    }
}