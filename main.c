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

#include "fdf.h"

int	close_window(void *param)
{
    t_fdf *fdf = (t_fdf *)param;
    free_resources(fdf);
    exit(0);
    return (0);
}

// int animate(t_fdf *fdf)
// {
//     int i = 10;
//     while (i > 0)
//         fdf->isometric_angle += 0.1;
//     usleep(200);
// }

int	handle_key(int key, t_fdf *fdf)
{
    if (key == 65307) // ESC key
        close_window(fdf);
    else if (key == 'z')
        fdf->z_scale++;
    else if (key == 'x')
        fdf->z_scale--;
    else if (key == 'r')
        fdf->isometric_angle += 0.1;
    else if (key == 't')
        fdf->isometric_angle -= 0.1;
    if (key == 'z' || key == 'x' || key == 'r' || key == 't')
    {
        mlx_destroy_image(fdf->mlx, fdf->img);
        fdf->img = mlx_new_image(fdf->mlx, fdf->win_width, fdf->win_height);
        fdf->data_addr = mlx_get_data_addr(fdf->img, &fdf->bpp, &fdf->size_line, &fdf->endian);
        mlx_clear_window(fdf->mlx, fdf->win);
        render_image_to_window(fdf);
        ft_printf("Key pressed : %d\n", key);
    }

    return (0);
}

void	free_map(t_fdf *fdf)
{
    int i = 0;

    if (fdf->map)
    {
        while (i < fdf->height)
        {
            free(fdf->map[i]);
            i++;
        }
        free(fdf->map);
    }
}

void	free_split_and_join(t_fdf *fdf)
{
    // if (fdf->split)
    //     free(fdf->split);
    // if (fdf->join)
    //     free(fdf->join);
    if (fdf->line)
        free(fdf->line);
    if (fdf->temp)
        free(fdf->temp);
    if (fdf->temp_join)
        free(fdf->temp_join);
    if (fdf->temp_split)
        free(fdf->temp_split);
}

void	free_mlx(t_fdf *fdf)
{
    if (fdf->img)
        mlx_destroy_image(fdf->mlx, fdf->img);
    if (fdf->win)
        mlx_destroy_window(fdf->mlx, fdf->win);
}

void	free_resources(t_fdf *fdf)
{
    free_map(fdf);
    free_split_and_join(fdf);
    free_mlx(fdf);
}

int	initialize_fdf(t_fdf *fdf, char *filename)
{
    ft_bzero(fdf, sizeof(t_fdf));
    fdf->z_scale = 5;
    fdf->isometric_angle = 0.6; // Initialize isometric angle
    if (read_file(fdf, filename) != 0)
    {
        free_resources(fdf);
        return (1);
    }
    if (process_map(fdf) != 0)
    {
        free_resources(fdf);
        return (1);
    }
    if (set_mlx_window(fdf) != 0)
    {
        free_resources(fdf);
        return (1);
    }
    return (0);
}

int	main(int argc, char **argv)
{
    t_fdf fdf;

    if (argc != 2)
    {
        write(1, "Usage: ./fdf <map_file>\n", 24);
        return (1);
    }
    if (initialize_fdf(&fdf, argv[1]) != 0)
        return (1);
    // mlx_loop_hook(fdf.mlx, animate, &fdf);
    mlx_key_hook(fdf.win, handle_key, &fdf);
    mlx_loop(fdf.mlx);
    free_resources(&fdf);
    return (0);
}
