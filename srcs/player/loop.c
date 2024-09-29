/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:51:22 by hdaher            #+#    #+#             */
/*   Updated: 2024/09/29 16:56:39 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief This function handles pressing a key
 *
 * This function is called every time a key is pressed and
 * updates the key attributes of the t_player structure in
 * data based on the key.

 * @param key Int value of the pressed key
 * @param data Pointer to t_data structure containing all data
 * @return 0
 */
int	key_press(int key, t_data *data)
{
	if (key == ESC_KEY)
		quit(data, 0);
	if (key == W_KEY)
		data->player->key_w = 1;
	if (key == A_KEY)
		data->player->key_a = 1;
	if (key == S_KEY)
		data->player->key_s = 1;
	if (key == D_KEY)
		data->player->key_d = 1;
	if (key == LEFT_ARROW)
		data->player->key_left = 1;
	if (key == RIGHT_ARROW)
		data->player->key_right = 1;
	if (key == E_KEY)
		door_interract(data);
	return (0);
}

/**
 * @brief This function handles releasing a key
 *
 * This function is called every time a key is released and
 * updates the key attributes of the t_player structure in
 * data based on the key.

 * @param key Int value of the released key
 * @param data Pointer to t_data structure containing all data
 * @return 0
 */
int	key_release(int key, t_data *data)
{
	if (key == W_KEY)
		data->player->key_w = 0;
	if (key == A_KEY)
		data->player->key_a = 0;
	if (key == S_KEY)
		data->player->key_s = 0;
	if (key == D_KEY)
		data->player->key_d = 0;
	if (key == LEFT_ARROW)
		data->player->key_left = 0;
	if (key == RIGHT_ARROW)
		data->player->key_right = 0;
	return (0);
}

void	release_keys(t_data *data)
{
	data->player->key_w = 0;
	data->player->key_a = 0;
	data->player->key_s = 0;
	data->player->key_d = 0;
	data->player->key_left = 0;
	data->player->key_right = 0;
}

/**
 * @brief This function updates the player direction based on mouse movement
 *
 * This function gets the mouse position using mlx_mouse_get_pos
 * and checks if the mouse is still in the screen. If it is, it calculates
 * the distance between the current mouse position and the last recorded
 * mouse position and updates the player direction accordingly.
 * If the distance is above MOUSE_THRESHOLD, the player direction isn't
 * updated to avoid 'inhuman' movements.
 *
 * @param data Pointer to the t_data structure containing all data
 */
void	get_mouse_direction(t_data *data)
{
	int	mouse_pos_x;
	int	mouse_pos_y;
	int	mouse_delta;

	mouse_pos_x = 0;
	mouse_pos_y = 0;
	GET_MOUSE_POS(data->mlx_ptr, data->win_ptr,
		mouse_pos_x, mouse_pos_y);
	if (mouse_pos_x >= 0 && mouse_pos_x <= SCREEN_WIDTH
		&& mouse_pos_y >= 0 && mouse_pos_y <= SCREEN_HEIGHT)
	{
		mouse_delta = ft_distance_to((double)mouse_pos_x, (double)mouse_pos_y,
				data->player->mouse_pos->x, data->player->mouse_pos->y);
		if (mouse_delta < MOUSE_THRESHOLD)
		{
			if ((double)mouse_pos_x > data->player->mouse_pos->x)
				rotate_player(data, ROTATION_SPEED * SENS * mouse_delta);
			else if ((double)mouse_pos_x < data->player->mouse_pos->x)
				rotate_player(data, -ROTATION_SPEED * SENS * mouse_delta);
		}
		data->player->mouse_pos->x = mouse_pos_x;
		data->player->mouse_pos->y = mouse_pos_y;
	}
	else
		release_keys(data);
}

/**
 * @brief This function handles player movement
 *
 * This function is called every frame of the game and checks
 * if the player is currently hodling a key by looking at the
 * key attributes of the t_player structure in data.
 * If key_w, key_a, key_s, or key_d are pressed, it calls the
 * move_player function.
 * If key_right or key_left are pressed, it calls the
 * rotate_player function.
 *
 * @param data Pointer to t_data structure containing all data
 * @return 0
 */
int	game_loop(t_data *data)
{
	static struct timeval	og;
	struct timeval			new;

	if (gettimeofday(&new, NULL) == -1)
		return (quit(data, 1), 0);
	if ((new.tv_sec - og.tv_sec) * 1000 + (new.tv_usec - og.tv_usec) / 1000 < 2)
		return (0);
	get_mouse_direction(data);
	if (data->player->key_w || data->player->key_a
		|| data->player->key_s || data->player->key_d)
		handle_movement(data);
	if (data->player->key_right)
		rotate_player(data, ROTATION_SPEED);
	if (data->player->key_left)
		rotate_player(data, -ROTATION_SPEED);
	raycast(data);
	render_hand(data);
	render_minimap(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->render->img_ptr, 0, 0);
	return (og.tv_sec = new.tv_sec, og.tv_usec = new.tv_usec, 0);
}
