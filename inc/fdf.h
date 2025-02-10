/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassih <anassih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 23:12:04 by anassih           #+#    #+#             */
/*   Updated: 2025/01/25 23:12:04 by anassih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../src/libft/inc/ft_printf.h"
# include "../src/libft/inc/get_next_line.h"
# include "../src/libft/inc/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <string.h>

# define WIN_WIDTH  800
# define WIN_HEIGHT 800


typedef struct s_transform
{
	int		i;
	int		j;
	int		x_offset;
	int		y_offset;
	int		x;
	int		y;
	int		z_scaled;

	float	scale_x;
	float	scale_y;
}			t_transform;

typedef struct s_line
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
}			t_line;

typedef struct s_map
{
	int		x;
	int		y;
	int		z;
	int		color;
}			t_map;

typedef struct s_fdf
{
	// File processing
	int		fd;
	int		count;
	char	*line;
	char	*join;
	char	*temp;
	char	*temp_join;
	char	**split;
	char	**temp_split;
	// Map data
	t_map	**map;
	int		max_width;
	int		row_size;
	int		width;
	int		height;
	// Window and rendering
	void	*mlx;
	void	*win;
	void	*img;
	char	*data_addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		win_width;
	int		win_height;
	int		z_scale;
	double	isometric_angle;
}			t_fdf;

// Function prototypes
int		read_file(t_fdf *fdf, char *filename);
int		parse_map(t_fdf *fdf);
int		process_map(t_fdf *fdf);
int		initialize_mlx(t_fdf *fdf);
int		render_image_to_window(t_fdf *fdf);
int		set_mlx_window(t_fdf *fdf);
int		get_color(int z, int z_min, int z_max);
int		close_window(void *param);
int		handle_key(int key, t_fdf *fdf);
int		initialize_fdf(t_fdf *fdf, char *filename);

void	draw_lines(t_fdf *fdf);

#endif