/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdaher <hdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:09:38 by hdaher            #+#    #+#             */
/*   Updated: 2024/09/04 13:08:34 by hdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_column_pos(t_image *texture, double y, int height)
{
	double	column_pos;

	column_pos = floor(((double)y / (double)height) * (double)texture->height);
	return (column_pos);
}

static int	get_line_pos(t_image *texture, double x, int height)
{
	double	line_pos;

	line_pos = floor(((double)x / (double)height) * (double)texture->height);
	return (line_pos);
}

static t_image	*get_texture(t_data *data, char c)
{
	if (c == 'D')
		return (data->door);
	else if (c == 'N')
		return (data->no);
	else if (c == 'S')
		return (data->so);
	else if (c == 'W')
		return (data->we);
	else
		return (data->ea);
}

void	get_wall_color(t_ray *ray, int *color, t_image *texture, int y)
{
	if (fmod(ray->wall_pos.y, 1) == 0)
		*color = *(int *)(texture->data_addr
				+ get_column_pos(texture, y, ray->height)
				* texture->size_line
				+ get_line_pos(texture, ray->height
					* fmod(ray->wall_pos.x, 1), ray->height)
				* (texture->bits_per_pixel / 8));
	else
		*color = *(int *)(texture->data_addr
				+ get_column_pos(texture, y, ray->height)
				* texture->size_line
				+ get_line_pos(texture, ray->height
					* fmod(ray->wall_pos.y, 1), ray->height)
				* (texture->bits_per_pixel / 8));
}

void	render_column(t_data *data, t_ray *ray)
{
	int		x;
	int		y;
	int		screen_y;
	int		color;
	t_image	*texture;

	texture = get_texture(data, ray->side);
	x = ray->screen_x;
	while (x < ray->screen_x + COL_WIDTH)
	{
		y = 0;
		if (ray->height > SCREEN_HEIGHT)
			y = (ray->height - SCREEN_HEIGHT) / 2;
		while (y < ray->height - 1
			&& y < SCREEN_HEIGHT + (ray->height - SCREEN_HEIGHT) / 2)
		{
			get_wall_color(ray, &color, texture, y);
			screen_y = (y + (SCREEN_HEIGHT / 2) - (int)(ray->height / 2));
			*(unsigned int *)(data->render->data_addr
					+ screen_y * data->render->size_line
					+ x * (data->render->bits_per_pixel / 8)) = color;
			y++;
		}
		x++;
	}
}
