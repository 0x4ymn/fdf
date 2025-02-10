/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassih <anassih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:22:44 by anassih           #+#    #+#             */
/*   Updated: 2025/01/31 18:22:44 by anassih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	transform_and_draw(t_fdf *fdf, int z_min, int z_max)
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
