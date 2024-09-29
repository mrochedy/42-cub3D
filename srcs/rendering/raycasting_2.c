/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdaher <hdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:50:17 by hdaher            #+#    #+#             */
/*   Updated: 2024/09/03 18:24:42 by hdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_dist(t_data *data, t_ray *ray,
	double dist, t_coord *dist_on_coord)
{
	ray->dist = dist;
	ray->wall_pos.x = data->player->pos->x + dist_on_coord->x;
	ray->wall_pos.y = data->player->pos->y + dist_on_coord->y;
}

static void	get_dist_to_closest(t_data *data, t_ray *ray,
	int closest_x, int closest_y)
{
	double	dist;
	t_coord	dist_on_coord;

	if (ray->dir.x)
	{
		dist_on_coord.x = closest_x - data->player->pos->x;
		dist_on_coord.y = (dist_on_coord.x / ray->dir.x) * ray->dir.y;
		dist = sqrt(pow(dist_on_coord.x, 2) + pow(dist_on_coord.y, 2));
		if (ray->dist < 0 || ray->dist > dist)
			update_dist(data, ray, dist, &dist_on_coord);
	}
	if (ray->dir.y)
	{
		dist_on_coord.y = closest_y - data->player->pos->y;
		dist_on_coord.x = (dist_on_coord.y / ray->dir.y) * ray->dir.x;
		dist = sqrt(pow(dist_on_coord.x, 2) + pow(dist_on_coord.y, 2));
		if (ray->dist < 0 || ray->dist > dist)
			update_dist(data, ray, dist, &dist_on_coord);
	}
}

static void	get_touched_tile(t_data *data, t_ray *ray)
{
	ray->touched_tile_x = floor(ray->wall_pos.x);
	if (ray->wall_pos.x == ray->touched_tile_x)
	{
		ray->side = 'W';
		if (ray->dir.x < 0)
		{
			ray->side = 'E';
			ray->touched_tile_x -= 1;
		}
	}
	ray->touched_tile_y = floor(ray->wall_pos.y);
	if (ray->wall_pos.y == ray->touched_tile_y)
	{
		ray->side = 'N';
		if (ray->dir.y < 0)
		{
			ray->side = 'S';
			ray->touched_tile_y -= 1;
		}
	}
	if (data->map[ray->touched_tile_y][ray->touched_tile_x] == 'D')
		ray->side = 'D';
}

void	get_dist_to_wall(t_data *data, t_ray *ray)
{
	int	closest_x;
	int	closest_y;

	if (ray->dir.x >= 0)
		closest_x = ceil(data->player->pos->x);
	else
		closest_x = floor(data->player->pos->x);
	if (ray->dir.y >= 0)
		closest_y = ceil(data->player->pos->y);
	else
		closest_y = floor(data->player->pos->y);
	while (1)
	{
		ray->dist = -1.0;
		get_dist_to_closest(data, ray, closest_x, closest_y);
		get_touched_tile(data, ray);
		if (data->map[ray->touched_tile_y][ray->touched_tile_x] == '1'
			|| data->map[ray->touched_tile_y][ray->touched_tile_x] == ' '
			|| data->map[ray->touched_tile_y][ray->touched_tile_x] == 'D')
			return ;
		if (ray->wall_pos.x == closest_x)
			closest_x += -1 + 2 * (ray->dir.x > 0);
		else
			closest_y += -1 + 2 * (ray->dir.y > 0);
	}
}
