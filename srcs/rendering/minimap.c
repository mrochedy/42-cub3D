/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdaher <hdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:07:23 by mrochedy          #+#    #+#             */
/*   Updated: 2024/09/04 13:04:18 by hdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_color_at_pixel(t_data *data, int x, int y, int color)
{
	*(unsigned int *)(data->render->data_addr
			+ y * data->render->size_line
			+ x * (data->render->bits_per_pixel / 8)) = color;
}

static void	render_minimap_pixel2(t_data *data, int i, int j)
{
	int	map_x;
	int	map_y;

	map_x = (data->player->pos->x * MINIMAP_TILE_SIZE + j) / MINIMAP_TILE_SIZE;
	map_y = (data->player->pos->y * MINIMAP_TILE_SIZE + i) / MINIMAP_TILE_SIZE;
	if (map_y < 0 || map_x < 0 || map_y > data->map_height
		|| map_x > data->map_width || !data->map[map_y]
		|| !data->map[map_y][map_x] || data->map[map_y][map_x] == ' ')
		set_color_at_pixel(data, j + MINIMAP_SIZE / 2 + MINIMAP_MARGIN,
			i + MINIMAP_SIZE / 2 + MINIMAP_MARGIN, 11448757);
	else if (data->map[map_y][map_x] == '1')
		set_color_at_pixel(data, j + MINIMAP_SIZE / 2 + MINIMAP_MARGIN,
			i + MINIMAP_SIZE / 2 + MINIMAP_MARGIN, 3223295);
	else if (data->map[map_y][map_x] == '0')
		set_color_at_pixel(data, j + MINIMAP_SIZE / 2 + MINIMAP_MARGIN,
			i + MINIMAP_SIZE / 2 + MINIMAP_MARGIN, 7171696);
	else if (data->map[map_y][map_x] == 'D')
		set_color_at_pixel(data, j + MINIMAP_SIZE / 2 + MINIMAP_MARGIN,
			i + MINIMAP_SIZE / 2 + MINIMAP_MARGIN, 16719360);
	else if (data->map[map_y][map_x] == 'd')
		set_color_at_pixel(data, j + MINIMAP_SIZE / 2 + MINIMAP_MARGIN,
			i + MINIMAP_SIZE / 2 + MINIMAP_MARGIN, 16736589);
	else
		set_color_at_pixel(data, j + MINIMAP_SIZE / 2 + MINIMAP_MARGIN,
			i + MINIMAP_SIZE / 2 + MINIMAP_MARGIN, 7171696);
}

static void	render_minimap_pixel1(t_data *data, int i, int j)
{
	int	half_size;

	half_size = MINIMAP_PLAYER_SIZE / 2;
	if (j >= -half_size && j <= half_size && i >= -half_size && i <= half_size)
		set_color_at_pixel(data, j + MINIMAP_SIZE / 2 + MINIMAP_MARGIN,
			i + MINIMAP_SIZE / 2 + MINIMAP_MARGIN, 16774177);
	else
		render_minimap_pixel2(data, i, j);
}

void	render_minimap(t_data *data)
{
	int	i;
	int	j;

	i = -MINIMAP_SIZE / 2 - 1;
	while (++i < MINIMAP_SIZE / 2)
	{
		j = -MINIMAP_SIZE / 2 - 1;
		while (++j < MINIMAP_SIZE / 2)
			render_minimap_pixel1(data, i, j);
	}
}
