/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdaher <hdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:40:55 by hdaher            #+#    #+#             */
/*   Updated: 2024/09/04 13:08:38 by hdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief This function replaces a pixel in the render img with a rainbow color
 *
 * This function generates a rgb rainbow color (using the sin function)
 * which depends on the hand_frame. It then replaces the pixel stored
 * in data->render->data_addr + render_pos to the rainbow color.
 *
 * @param data Pointer to the t_data structure containing all game data
 * @param render_pos Position of the pixel
 */
void	rainbow(t_data *data, int render_pos)
{
	int	r;
	int	g;
	int	b;

	r = (int)(127 * (sin(data->hand_frame / 100.0) + 1.0));
	g = (int)(127 * (sin(data->hand_frame / 100.0 + 2.0) + 1));
	b = (int)(127 * (sin(data->hand_frame / 100.0 + 4.0) + 1));
	*(int *)(data->render->data_addr + render_pos)
		= r;
	*(int *)(data->render->data_addr + render_pos + 1)
		= g;
	*(int *)(data->render->data_addr + render_pos + 2)
		= b;
	*(int *)(data->render->data_addr + render_pos + 3)
		= 255;
}

/**
 * @brief This function adds a pixel of the hand to the render image
 *
 * This function calculates the position of a pixel in the render image
 * and the hand image with a given x and y, and replaces the pixel
 * in the render image with the corresponding pixel of the hand texture
 * according to y_frame (current hand animation frame). If a pixel with
 * bgrt values of (*, -1, *, *) is found, it doesnt add the pixel to
 * the render image, and if a pixel with brt values of (*, *, -1, *) is
 * found, it replaces it with a rainbow color (calling the rainbow).
 *
 * @param data Pointer to the t_data structure containing all game data
 * @param x x position on the screen
 * @param y y position on the screen
 * @param y_frame Current frame of the hand animation
 */
void	add_hand_to_render(t_data *data, int x, int y, int y_frame)
{
	int	hand_pos;
	int	render_pos;

	hand_pos = y * data->hand->size_line
		+ x * (data->hand->bits_per_pixel / 8);
	render_pos = (y + y_frame + SCREEN_HEIGHT - data->hand->height)
		* data->render->size_line
		+ (x + SCREEN_WIDTH - data->hand->width)
		* (data->render->bits_per_pixel / 8);
	if ((int)*(data->hand->data_addr + hand_pos + 2) == -1)
		rainbow(data, render_pos);
	else if ((int)*(data->hand->data_addr + hand_pos + 1) != -1)
	{
		*(data->render->data_addr + render_pos)
			= *(data->hand->data_addr + hand_pos);
		*(data->render->data_addr + render_pos + 1)
			= *(data->hand->data_addr + hand_pos + 1);
		*(data->render->data_addr + render_pos + 2)
			= *(data->hand->data_addr + hand_pos + 2);
		*(data->render->data_addr + render_pos + 3)
			= *(data->hand->data_addr + hand_pos + 3);
	}
}
/**
 * @brief This function adds the hand animation to the render image
 *
 * This function loops through the hand sprite and adds every pixel
 * to the render image. It loops through the hand sprite width and height
 * and calls the add_hand_to_render for each  x and y. It also increments
 * the hand's current animation frame up to 600 or resets it to 0
 * if the hand reaches it's last animation frame.
 *
 * @param data Pointer to the t_data structure containing all game data
 */

void	render_hand(t_data *data)
{
	int	x;
	int	y;
	int	y_frame;

	if (data->hand_frame < 300)
		y_frame = data->hand_frame / 10;
	else
		y_frame = (600 - data->hand_frame) / 10;
	x = 0;
	while (x < data->hand->width)
	{
		y = 0;
		while (y < data->hand->height - y_frame)
		{
			add_hand_to_render(data, x, y, y_frame);
			y++;
		}
		x++;
	}
	if (data->hand_frame < 600)
		data->hand_frame++;
	else
		data->hand_frame = 0;
}
