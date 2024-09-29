/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdaher <hdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:51:16 by mrochedy          #+#    #+#             */
/*   Updated: 2024/09/03 15:05:28 by hdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	deal_with_collisions(t_data *data, t_coord *old_pos,
	t_coord *new_pos)
{
	char	**map;
	int		x;
	int		y;

	map = data->map;
	x = floor(new_pos->x);
	y = floor(new_pos->y);
	if (map[y][x] && map[y][x] != '1' && map[y][x] != ' ' && map[y][x] != 'D')
		return ;
	x = floor(new_pos->x);
	y = floor(old_pos->y);
	if (map[y][x] && map[y][x] != '1' && map[y][x] != ' ' && map[y][x] != 'D')
	{
		new_pos->y = old_pos->y;
		return ;
	}
	x = floor(old_pos->x);
	y = floor(new_pos->y);
	if (map[y][x] && map[y][x] != '1' && map[y][x] != ' ' && map[y][x] != 'D')
	{
		new_pos->x = old_pos->x;
		return ;
	}
	new_pos->x = old_pos->x;
	new_pos->y = old_pos->y;
}
