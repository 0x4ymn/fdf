/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anassih <anassih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:35:19 by anassih           #+#    #+#             */
/*   Updated: 2025/01/23 15:35:19 by anassih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
    t_fdf   fdf;

    if (ac != 2)
    {
        ft_printf("Usage: ./fdf <filename>\n");
        return (1);
    }
    fdf.fd = open(av[1], O_RDONLY);
	if (fdf.fd == -1)
	{
		perror("Error opening map file");
		return (1);
	}
    fdf.count = 0;
    fdf.join = ft_strdup("");
	while ((fdf.line = get_next_line(fdf.fd)) != NULL)
	{
        fdf.join = ft_strjoin(fdf.join, fdf.line);
		fdf.count++;
		free(fdf.line);
	}
    fdf.split = ft_split(fdf.join, '\n');
    for (int i = 0; i < fdf.count; i++)
    {
        ft_printf("%s\n", fdf.split[i]);
        free(fdf.split[i]);
    }
    ft_printf("Lines counted: %d\n", fdf.count);
    fdf.map = (int **)malloc(sizeof(int *) * fdf.count);
    int i = 0;
    while (i < fdf.count)
    {
        fdf.map[i] = (int *)malloc(sizeof(int) * fdf.count);
        fdf.temp_split = ft_split(fdf.split[i], ' ');
        int j = 0;
        while (fdf.temp_split[j])
        {
            fdf.map[i][j] = ft_atoi(fdf.temp_split[j]);
            free(fdf.temp_split[j]);
            j++;
        }
        free(fdf.temp_split);
        i++;
    }
    free(fdf.join);
    free(fdf.split);
	close(fdf.fd);
	return (0);
}