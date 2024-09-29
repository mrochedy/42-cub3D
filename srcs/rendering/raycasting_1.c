/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdaher <hdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:53:17 by mrochedy          #+#    #+#             */
/*   Updated: 2024/09/04 13:08:28 by hdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	send_ray(t_data *data, t_coord *plane, int x)
{
	double	camera_x;
	t_ray	ray;

	camera_x = 2 * ((double)x / SCREEN_WIDTH) - 1;
	ray.dir.x = data->player->dir->x + plane->x * camera_x;
	ray.dir.y = data->player->dir->y + plane->y * camera_x;
	ray.screen_x = x;
	get_dist_to_wall(data, &ray);
	ray.dist = ray.dist * cos(atan2(ray.dir.x, ray.dir.y)
			- atan2(data->player->dir->x, data->player->dir->y));
	ray.height = SCREEN_HEIGHT / ray.dist;
	render_column(data, &ray);
}

/**
 * @brief This function performs a raycasting in the FOV angle
 *
 * This function first calculates the plane vector, then creates a copy
 * of the background image containing the ceiling and floor colors. It then
 * loops through the SCREEN_WIDTH and sends SCREEN_WIDTH/COL_WIDTH rays
 * in the FOV angle calling the send_ray function.
 *
 * @param data Pointer to the t_data structure containg all the game data
 */
void	raycast(t_data *data)
{
	t_coord	plane;
	int		x;
	double	plane_length;

	plane_length = tanf(FOV * ((M_PI / 180.0)) / 2.0);
	ft_memcpy(data->render->data_addr, data->background->data_addr,
		SCREEN_HEIGHT * data->background->size_line);
	plane.x = -data->player->dir->y * plane_length;
	plane.y = data->player->dir->x * plane_length;
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		send_ray(data, &plane, x);
		x += COL_WIDTH;
	}
}
