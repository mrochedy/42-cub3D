/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:45:16 by mrochedy          #+#    #+#             */
/*   Updated: 2024/09/29 16:43:28 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_images(t_data *data)
{
	if (data->mlx_ptr && data->no->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->no->img_ptr);
	if (data->mlx_ptr && data->so->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->so->img_ptr);
	if (data->mlx_ptr && data->we->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->we->img_ptr);
	if (data->mlx_ptr && data->ea->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->ea->img_ptr);
	if (data->mlx_ptr && data->door->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->door->img_ptr);
	if (data->mlx_ptr && data->hand->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->hand->img_ptr);
	if (data->mlx_ptr && data->render->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->render->img_ptr);
	if (data->mlx_ptr && data->background->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->background->img_ptr);
	free(data->so);
	free(data->no);
	free(data->we);
	free(data->ea);
	free(data->render);
	free(data->door);
	free(data->hand);
	free(data->background);
}

void	quit(t_data *data, int err_code)
{
	ft_free_tab((void **)data->map, -1);
	ft_free_tab((void **)data->scene, -1);
	if (data->so)
		free(data->so->path);
	if (data->no)
		free(data->no->path);
	if (data->we)
		free(data->we->path);
	if (data->ea)
		free(data->ea->path);
	free_images(data);
	if (data->player)
	{
		free(data->player->pos);
		free(data->player->dir);
		free(data->player->mouse_pos);
		free(data->player);
	}
	if (data->mlx_ptr && data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
		DESTROY_DISPLAY(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(err_code);
}

int	close_window(t_data *data)
{
	quit(data, 0);
	return (0);
}

void	init_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		quit(data, 1);
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	if (!data->win_ptr)
		quit(data, 1);
	mlx_hook(data->win_ptr, DESTROYNOTIFY, STRUCTURENOTIFYMASK,
		&close_window, data);
	mlx_hook(data->win_ptr, KEYPRESS, KEYPRESSMASK, &key_press, data);
	mlx_hook(data->win_ptr, KEYRELEASE, KEYRELEASEMASK, &key_release, data);
	mlx_loop_hook(data->mlx_ptr, &game_loop, data);
}
