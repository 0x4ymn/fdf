/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassih <anassih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 01:11:22 by anassih           #+#    #+#             */
/*   Updated: 2025/01/26 01:11:22 by anassih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int get_color(int z, int z_min, int z_max)
{
    double	percentage;
    int		red;
    int		green;
    int		blue;

    if (z_max == z_min)
        return (0xFFFFFF); // Default color if no height difference
    percentage = (double)(z - z_min) / (z_max - z_min);
    red = (int)(255 * percentage);
    green = 25;
    blue = (int)(255 * (1 - percentage));
    return ((red << 10) | (green << 10) | blue);
}
