/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassih <anassih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:25:00 by anassih           #+#    #+#             */
/*   Updated: 2025/01/30 16:25:00 by anassih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	put_pixel(t_fdf *fdf, int x, int y, int color)
{
	int	pixel_pos;

	if (x >= 0 && x < fdf->win_width && y >= 0 && y < fdf->win_height)
	{
		pixel_pos = (y * fdf->size_line) + (x * (fdf->bpp / 8));
		*((unsigned int *)(fdf->data_addr + pixel_pos)) = color;
	}
}

static void	draw_line_loop(t_fdf *fdf, t_line *line, int x0, int y0, int x1,
		int y1, int color)
{
	while (1)
	{
		put_pixel(fdf, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		line->e2 = line->err * 2;
		if (line->e2 > -line->dy)
		{
			line->err -= line->dy;
			x0 += line->sx;
		}
		if (line->e2 < line->dx)
		{
			line->err += line->dx;
			y0 += line->sy;
		}
	}
}

static void	draw_line(t_fdf *fdf, int x0, int y0, int x1, int y1, int color)
{
	t_line	line;

	line.dx = abs(x1 - x0);
	line.dy = abs(y1 - y0);
	line.err = line.dx - line.dy;
	if (x0 < x1)
		line.sx = 1;
	else
		line.sx = -1;
	if (y0 < y1)
		line.sy = 1;
	else
		line.sy = -1;
	draw_line_loop(fdf, &line, x0, y0, x1, y1, color);
}

void	draw_lines(t_fdf *fdf)
{
	int i;
	int j;

	i = 0;
	while (i < fdf->height)
	{
		j = 0;
		while (j < fdf->width)
		{
			if (j < fdf->width - 1)
				draw_line(fdf, fdf->map[i][j].x, fdf->map[i][j].y, fdf->map[i][j
					+ 1].x, fdf->map[i][j + 1].y, fdf->map[i][j].color);
			if (i < fdf->height - 1)
				draw_line(fdf, fdf->map[i][j].x, fdf->map[i][j].y, fdf->map[i
					+ 1][j].x, fdf->map[i + 1][j].y, fdf->map[i][j].color);
			j++;
		}
		i++;
	}
}