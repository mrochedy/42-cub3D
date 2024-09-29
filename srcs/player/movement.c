/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdaher <hdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:35:54 by hdaher            #+#    #+#             */
/*   Updated: 2024/09/03 18:27:04 by hdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief This function updates the player position
 *
 * This function looks at the player key attribute and moves
 * the player according to the speed passed as a parameter.
 *
 * @param data Pointer to t_data structure containing all data
 * @param speed Normalized player speed (either 1 or sqrt(2)/2)
 * @return
 */
void	move_player(t_data *data, double speed)
{
	if (data->player->key_w)
	{
		data->player->pos->x += speed * (data->player->dir->x);
		data->player->pos->y += speed * (data->player->dir->y);
	}
	if (data->player->key_a)
	{
		data->player->pos->x += speed * (data->player->dir->y);
		data->player->pos->y -= speed * (data->player->dir->x);
	}
	if (data->player->key_s)
	{
		data->player->pos->x -= speed * (data->player->dir->x);
		data->player->pos->y -= speed * (data->player->dir->y);
	}
	if (data->player->key_d)
	{
		data->player->pos->x -= speed * (data->player->dir->y);
		data->player->pos->y += speed * (data->player->dir->x);
	}
}

/**
 * @brief This function updates the player position
 *
 * This function is called every time the key_w, key_a, key_s or
 * key_d attribute of the player structure is set to 1
 * instead of 0, and calls the move_player function giving it the
 * normalized speed. It then calls the deal_with_collisions function
 * to check for potential wall collisions.

 * @param data Pointer to t_data structure containing all data
 * @return
 */
void	handle_movement(t_data *data)
{
	t_coord	old_pos;
	double	speed;

	if ((data->player->key_w && data->player->key_a)
		|| (data->player->key_a && data->player->key_s)
		|| (data->player->key_s && data->player->key_d)
		|| (data->player->key_d && data->player->key_w))
		speed = SPEED * sqrt(2) / 2;
	else
		speed = SPEED;
	old_pos.x = data->player->pos->x;
	old_pos.y = data->player->pos->y;
	move_player(data, speed);
	deal_with_collisions(data, &old_pos, data->player->pos);
}
// to print player position
// printf("x : %f | y : %f\n", data->player->pos->x, data->player->pos->y);

/**
 * @brief This function updates the player direction
 *
 * This function is called every time the key_right or key_left
 * attribute of the player structure is set to 1 instead of 0
 * and updates the direction t_coord structure in player
 * based on the rotation speed parameter.

 * @param data Pointer to t_data structure containing all data
 * @return
 */
void	rotate_player(t_data *data, double rotation_speed)
{
	double	old_dir_x;

	old_dir_x = data->player->dir->x;
	data->player->dir->x
		= data->player->dir->x * cos((double)rotation_speed)
		- data->player->dir->y * sin((double)rotation_speed);
	data->player->dir->y
		= old_dir_x * sin((double)rotation_speed)
		+ data->player->dir->y * cos((double)rotation_speed);
}

void	door_interract(t_data *data)
{
	int	x;
	int	y;

	x = floor(data->player->pos->y);
	y = floor(data->player->pos->x);
	if (data->map[x + 1][y] == 'D')
		data->map[x + 1][y] = 'd';
	else if (data->map[x + 1][y] == 'd')
		data->map[x + 1][y] = 'D';
	if (data->map[x - 1][y] == 'D')
		data->map[x - 1][y] = 'd';
	else if (data->map[x - 1][y] == 'd')
		data->map[x - 1][y] = 'D';
	if (data->map[x][y + 1] == 'D')
		data->map[x][y + 1] = 'd';
	else if (data->map[x][y + 1] == 'd')
		data->map[x][y + 1] = 'D';
	if (data->map[x][y - 1] == 'D')
		data->map[x][y - 1] = 'd';
	else if (data->map[x][y - 1] == 'd')
		data->map[x][y - 1] = 'D';
}
