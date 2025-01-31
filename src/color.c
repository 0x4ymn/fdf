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

#include "../inc/fdf.h"

int get_color(int z, int z_min, int z_max)
{
    double ratio;
    int red;
    int green;
    int blue;

    if (z_min == z_max)
        return (0xFFFFFF);
    ratio = (double)(z - z_min) / (z_max - z_min);
    red = (int)(255 * ratio);
    green = (int)(255 * (1 - ratio));
    blue = 200;
    return ((red << 16) | (green << 8) | blue);
}
