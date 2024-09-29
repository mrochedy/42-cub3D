/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdaher <hdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:46:17 by hdaher            #+#    #+#             */
/*   Updated: 2024/09/03 18:24:42 by hdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	malloc_images(t_data *data)
{
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->door = NULL;
	data->hand = NULL;
	data->background = NULL;
	data->render = NULL;
	data->no = malloc(sizeof(t_image));
	data->so = malloc(sizeof(t_image));
	data->we = malloc(sizeof(t_image));
	data->ea = malloc(sizeof(t_image));
	data->door = malloc(sizeof(t_image));
	data->hand = malloc(sizeof(t_image));
	data->background = malloc(sizeof(t_image));
	data->render = malloc(sizeof(t_image));
	if (!data->no || !data->so || !data->we || !data->ea
		|| !data->door || !data->hand
		|| !data->background || !data->render)
		quit(data, 1);
}

/**
 * @brief This function initiates all images in data
 *
 * This function mallocs all t_image structures in data
 * and initiates all their attributes to default values.
 * If any mallocs fails, quit is called with error code 1
 *
 * @param data Pointer to t_data structure containing all data
 * @return
 */
void	init_images(t_data *data)
{
	malloc_images(data);
	data->so->img_ptr = NULL;
	data->we->img_ptr = NULL;
	data->ea->img_ptr = NULL;
	data->door->img_ptr = NULL;
	data->hand->img_ptr = NULL;
	data->background->img_ptr = NULL;
	data->render->img_ptr = NULL;
	data->no->path = NULL;
	data->so->path = NULL;
	data->we->path = NULL;
	data->ea->path = NULL;
}

/**
 * @brief This function creates all images needed for rendering
 *
 * This function calls the mlx_xpm_file_to_image function to
 * create all images using their paths and stores a pointer
 * to the image into data.
 *
 * @param data Pointer to t_data structure containing all data
 * @return
 */
void	*create_images(t_data *data)
{
	data->no->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
			data->no->path, &data->no->width, &data->no->height);
	data->so->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
			data->so->path, &data->so->width, &data->so->height);
	data->we->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
			data->we->path, &data->we->width, &data->we->height);
	data->ea->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
			data->ea->path, &data->ea->width, &data->ea->height);
	data->door->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
			"./textures/metal_door.xpm",
			&data->door->width, &data->door->height);
	data->hand->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
			"./textures/hand.xpm",
			&data->hand->width, &data->hand->height);
	data->background->img_ptr = mlx_new_image(data->mlx_ptr,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	data->render->img_ptr = mlx_new_image(data->mlx_ptr,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!data->no->img_ptr || !data->so->img_ptr || !data->we->img_ptr
		|| !data->ea->img_ptr || !data->background->img_ptr
		|| !data->door->img_ptr || !data->hand->img_ptr
		|| !data->render->img_ptr)
		return (ft_putstr_fd(IMG_ERR, 2), quit(data, 1), NULL);
	return (NULL);
}

/**
 * @brief This function gets data of all images in data
 *
 * This function calls the mlx_get_data_addr function for
 * each t_image structure in data, to get the values of
 * data_addr, bits_per_pixel, size_line and endian.
 *
 * @param data Pointer to t_data structure containing all data
 * @return
 */
void	get_images_data(t_data *data)
{
	data->no->data_addr = mlx_get_data_addr(data->no->img_ptr,
			&data->no->bits_per_pixel, &data->no->size_line, &data->no->endian);
	data->so->data_addr = mlx_get_data_addr(data->so->img_ptr,
			&data->so->bits_per_pixel, &data->so->size_line, &data->so->endian);
	data->we->data_addr = mlx_get_data_addr(data->we->img_ptr,
			&data->we->bits_per_pixel, &data->we->size_line, &data->we->endian);
	data->ea->data_addr = mlx_get_data_addr(data->ea->img_ptr,
			&data->ea->bits_per_pixel, &data->ea->size_line, &data->ea->endian);
	data->background->data_addr = mlx_get_data_addr(data->background->img_ptr,
			&data->background->bits_per_pixel, &data->background->size_line,
			&data->background->endian);
	data->render->data_addr = mlx_get_data_addr(data->render->img_ptr,
			&data->render->bits_per_pixel, &data->render->size_line,
			&data->render->endian);
	data->door->data_addr = mlx_get_data_addr(data->door->img_ptr,
			&data->door->bits_per_pixel, &data->door->size_line,
			&data->door->endian);
	data->hand->data_addr = mlx_get_data_addr(data->hand->img_ptr,
			&data->hand->bits_per_pixel, &data->hand->size_line,
			&data->hand->endian);
}

/**
 * @brief This function creates images for the floor and ceiling
 *
 * This function creates the screen image of size SCREEN_WIDTH
 * by SCREEN_HEIGHT and fills every pixel of the image with the
 * int color values contained in data->ceil_color and
 * data->floor_color.
 *
 * @param data Pointer to t_data structure containing all data
 * @return
 */
void	create_background(t_data *data)
{
	int	x;
	int	y;
	int	pos;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT)
		{
			pos = (y * data->background->size_line
					+ x * (data->background->bits_per_pixel / 8));
			if (y < SCREEN_HEIGHT / 2)
				*(unsigned int *)(data->background->data_addr + pos)
					= data->ceil_color;
			else
				*(unsigned int *)(data->background->data_addr + pos)
					= data->floor_color;
			y++;
		}
		x++;
	}
}
