/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdaher <hdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:06:00 by mrochedy          #+#    #+#             */
/*   Updated: 2024/09/04 12:55:41 by hdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Checks if the map contains valid chars
 *
 * This function checks if all the chars composing the map are valid. The only
 * valid chars are '0', '1', 'N', 'S', 'E', 'W' and ' '. It also checks if
 * there's strictly one start position.
 *
 * @param data Struct object containing all the program data
 * @return void* Always NULL
 */
static void	*check_valid_chars(t_data *data)
{
	int	row;
	int	col;
	int	start_pos_count;

	row = -1;
	start_pos_count = 0;
	while (data->map[++row])
	{
		col = -1;
		while (data->map[row][++col])
		{
			if (data->map[row][col] != '0' && data->map[row][col] != '1'
				&& data->map[row][col] != 'N' && data->map[row][col] != 'S'
				&& data->map[row][col] != 'E' && data->map[row][col] != 'W'
				&& data->map[row][col] != ' ' && data->map[row][col] != 'D')
				return (ft_putstr_fd(MAP_CHARS_ERR, 2),
					quit(data, 1), NULL);
			if (data->map[row][col] == 'N' || data->map[row][col] == 'S'
				|| data->map[row][col] == 'E' || data->map[row][col] == 'W')
				start_pos_count++;
		}
	}
	if (start_pos_count != 1)
		return (ft_putstr_fd(MAP_START_ERR, 2), quit(data, 1), NULL);
	return (NULL);
}

/**
 * @brief Checks if a space char is valid
 *
 * This function checks if a space char is indeed surrounded either by a '1',
 * another space or NULL. If that's not the case, the map is invalid.
 *
 * @param data Struct object containing all the program data
 * @param row Integer containing the current row index
 * @param col Integer containing the current column index
 */
static void	*check_spaces(t_data *data, int row, int col)
{
	if (row > 0 && data->map[row - 1][col] && data->map[row - 1][col] != ' '
		&& data->map[row - 1][col] != '1')
		return (ft_putstr_fd(MAP_CLOSED_ERR, 2), quit(data, 1), NULL);
	if (col > 0 && data->map[row][col - 1] && data->map[row][col - 1] != ' '
		&& data->map[row][col - 1] != '1')
		return (ft_putstr_fd(MAP_CLOSED_ERR, 2), quit(data, 1), NULL);
	if (data->map[row + 1] && data->map[row + 1][col]
		&& data->map[row + 1][col] != ' ' && data->map[row + 1][col] != '1')
		return (ft_putstr_fd(MAP_CLOSED_ERR, 2), quit(data, 1), NULL);
	if (data->map[row][col + 1] && data->map[row][col + 1] != ' '
		&& data->map[row][col + 1] != '1')
		return (ft_putstr_fd(MAP_CLOSED_ERR, 2), quit(data, 1), NULL);
	return (NULL);
}

/**
 * @brief Checks if the map is indeed closed by walls
 *
 * This function checks if the map is closed by walls. For a map to be closed,
 * The first and last chars of each row and column need to be either '1' or a
 * space and each space needs to be surrounded either by a '1', another space
 * or NULL.
 *
 * @param data Struct object containing all the program data
 */
static void	*check_map_closed(t_data *data)
{
	int	row;
	int	col;

	row = -1;
	while (data->map[++row])
	{
		col = -1;
		while (data->map[row][++col])
		{
			if (row == 0 || col == 0 || !data->map[row + 1])
				if (data->map[row][col] != '1' && data->map[row][col] != ' ')
					return (ft_putstr_fd(MAP_CLOSED_ERR, 2),
						quit(data, 1), NULL);
			if (data->map[row][col] == ' ')
				check_spaces(data, row, col);
		}
		if (col > 0 && data->map[row][col - 1] && data->map[row][col - 1] != '1'
				&& data->map[row][col - 1] != ' ')
			return (ft_putstr_fd(MAP_CLOSED_ERR, 2), quit(data, 1), NULL);
	}
	return (NULL);
}

/**
 * @brief Gets the maximum line length
 *
 * This function loops in the map lines and finds the maximum length.
 * It then returns it.
 *
 * @param data Struct object containing all the program data
 */
static int	get_max_row_len(t_data *data)
{
	int	i;
	int	max_row_len;
	int	row_len;
	int	is_empty_line;

	i = 0;
	max_row_len = 0;
	row_len = 0;
	is_empty_line = 0;
	while (data->scene[data->map_start_line + i])
	{
		row_len = ft_strlen(data->scene[data->map_start_line + i]);
		if (is_empty_line == 1 && row_len != 0)
			return (free(data->map), data->map = NULL,
				ft_putstr_fd(MAP_EMPTY_LINE_ERR, 2), quit(data, 1), 0);
		if (row_len == 0)
			is_empty_line = 1;
		if (row_len > max_row_len)
			max_row_len = row_len;
		i++;
	}
	while (!data->scene[data->map_start_line + i - 1][0])
		i--;
	return (data->map_width = max_row_len, data->map_height = i, max_row_len);
}

/**
 * @brief Reads and stores the map
 *
 * This function first finds the start of the map and counts the map size
 * to allocate the map, which is an array of String. It gets the maximum
 * row length, to allocate each line to this maximum length and avoid
 * invalid reads. It then stores the map and launches the validity checks.
 *
 * @param data Struct object containing all the program data
 * @return void* Always NULL
 */
void	*read_map(t_data *data)
{
	int	i;
	int	map_len;
	int	max_len;

	while (data->scene[data->map_start_line]
		&& !data->scene[data->map_start_line][0])
		data->map_start_line++;
	map_len = 0;
	while (data->scene[data->map_start_line + map_len])
		map_len++;
	data->map = malloc(sizeof(char *) * (map_len + 1));
	if (!data->map)
		quit(data, 1);
	i = 0;
	max_len = get_max_row_len(data);
	while (data->scene[data->map_start_line + i])
	{
		data->map[i] = ft_strldup(data->scene[data->map_start_line + i],
				max_len, ' ');
		if (!data->map[i++])
			return (ft_free_tab((void **)data->map, i - 1), data->map = NULL,
				quit(data, 1), NULL);
	}
	data->map[i] = NULL;
	return (check_valid_chars(data), check_map_closed(data), NULL);
}
