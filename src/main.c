/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassih <anassih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 23:35:20 by anassih           #+#    #+#             */
/*   Updated: 2025/01/25 23:35:20 by anassih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int close_window(void *param)
{
    t_fdf *fdf;

    fdf = (t_fdf *)param;
    if (fdf->map)
    {
        int i;

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

int handle_key(int key, t_fdf *fdf)
{
    if (key == 65307) // ESC key
        close_window(fdf);
    // if (key == 'z') // Left arrow key
    //     fdf->isometric_angle -= 0.05;
    // if (key == 'x') // Right arrow key
    //     fdf->isometric_angle += 0.05;
    // if (key == 'c') // Down arrow key
    //     fdf->z_scale -= 1;
    // if (key == 'v') // Up arrow key
    //     fdf->z_scale += 1;
    // if (key == 'z' || key == 'x' || key == 'c' || key == 'v')
    // {
    //     mlx_destroy_image(fdf->mlx, fdf->img);
    //     fdf->img = mlx_new_image(fdf->mlx, fdf->win_width, fdf->win_height);
    //     fdf->data_addr = mlx_get_data_addr(fdf->img, &fdf->bpp, &fdf->size_line, &fdf->endian);
    //     mlx_clear_window(fdf->mlx, fdf->win);
    //     render_image_to_window(fdf);
    // }
    return (0);
}

int	initialize_fdf(t_fdf *fdf, char *filename)
{
    ft_bzero(fdf, sizeof(t_fdf));
    fdf->z_scale = 4;
    fdf->isometric_angle = 0.8; // Initialize isometric angle
    if (read_file(fdf, filename) != 0)
        return (1);
    if (process_map(fdf) != 0)
        return (1);
    if (set_mlx_window(fdf) != 0)
        return (1);
    return (0);
}

int	main(int argc, char **argv)
{
    t_fdf fdf;

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
