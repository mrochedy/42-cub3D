/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdaher <hdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:08:33 by mrochedy          #+#    #+#             */
/*   Updated: 2024/09/30 14:57:36 by hdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->scene = NULL;
	data->map = NULL;
	data->player = NULL;
	data->map_start_line = 0;
	init_images(data);
	init_player(data);
	data->floor_color = -1;
	data->ceil_color = -1;
	data->hand_frame = 0;
}

int	main(int argc, char **argv)
{
	int		arg_len;
	t_data	data;

	if (argc != 2)
		return (ft_putstr_fd(ARGS_ERR, 2), 1);
	arg_len = ft_strlen(argv[1]);
	if (arg_len < 4 || argv[1][arg_len - 1] != 'b'
		|| argv[1][arg_len - 2] != 'u' || argv[1][arg_len - 3] != 'c'
		|| argv[1][arg_len - 4] != '.')
		return (ft_putstr_fd(FILE_EXTENSION_ERR, 2), 1);
	init_data(&data);
	read_scene(&data, argv[1]);
	read_map(&data);
	get_player_starting_attributes(&data);
	init_window(&data);
	create_images(&data);
	get_images_data(&data);
	create_background(&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}

// Add to main to test print wall with render column
	// int	i = 100;
	// int	height = 200;
	// while (i < 164)
	// {
	// 	render_column(&data, data.no, i, height);
	// 	height -= 1;
	// 	i++;
	// }
