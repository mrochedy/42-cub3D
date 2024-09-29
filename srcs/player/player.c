/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdaher <hdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:05:12 by hdaher            #+#    #+#             */
/*   Updated: 2024/09/03 16:55:58 by hdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Gets the player's starting position and direction
 *
 * This function finds the starting position of the player in the map and
 * its orientation (or direction), depending on the starting char
 * ('N', 'S', 'E' or 'W').
 *
 * @param data Struct object containing all the program data
 */
void	*get_player_starting_attributes(t_data *data)
{
	int	row;
	int	col;

	data->player->dir->x = 0.0;
	data->player->dir->y = 0.0;
	row = -1;
	while (data->map[++row])
	{
		col = -1;
		while (data->map[row][++col])
		{
			data->player->pos->x = col + 0.5;
			data->player->pos->y = row + 0.5;
			if (data->map[row][col] == 'N')
				return (data->player->dir->y = -1.0, NULL);
			else if (data->map[row][col] == 'S')
				return (data->player->dir->y = 1.0, NULL);
			else if (data->map[row][col] == 'E')
				return (data->player->dir->x = 1.0, NULL);
			else if (data->map[row][col] == 'W')
				return (data->player->dir->x = -1.0, NULL);
		}
	}
	return (NULL);
}

/**
 * @brief This function initiates the player structure in data
 *
 * This function mallocs the t_player structure in data, and
 * the position and direction t_coord structures in the t_player
 * structure. It then initiates all of it's attributes to default
 * values. If any mallocs fails, quit is called with error code 1
 *
 * @param data Pointer to t_data structure containing all data
 * @return
 */
void	init_player(t_data *data)
{
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		quit(data, 1);
	data->player->pos = NULL;
	data->player->dir = NULL;
	data->player->mouse_pos = NULL;
	data->player->pos = malloc(sizeof(t_coord));
	data->player->mouse_pos = malloc(sizeof(t_coord));
	data->player->dir = malloc(sizeof(t_coord));
	if (!data->player->pos || !data->player->dir
		|| !data->player->mouse_pos)
		quit(data, 1);
	data->player->mouse_pos->x = 0.0;
	data->player->mouse_pos->y = 0.0;
	data->player->key_w = 0;
	data->player->key_a = 0;
	data->player->key_s = 0;
	data->player->key_d = 0;
	data->player->key_left = 0;
	data->player->key_right = 0;
}
