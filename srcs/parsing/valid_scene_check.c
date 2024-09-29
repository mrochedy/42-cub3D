/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_scene_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdaher <hdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:05:10 by mrochedy          #+#    #+#             */
/*   Updated: 2024/09/04 10:34:54 by hdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Checks if a color info is valid
 *
 * This function checks if there are more than 3 commas, if there are
 * other chars than digits and if the size of the splitted color is not
 * exactly 3 and if that's the case, the color is invalid.
 *
 * @param data Struct object containing all the program data
 * @param spl Array of String containing the splitted line
 * @param rgb_spl Array of String containing the splitted color
 */
static void	check_valid_color(t_data *data, char **spl, char **rgb_spl)
{
	int		i;
	int		commas_count;
	int		is_invalid;

	i = 0;
	commas_count = 0;
	is_invalid = 0;
	while (spl[1][i])
	{
		if ((spl[1][i] < '0' || spl[1][i] > '9') && spl[1][i] != ',')
			is_invalid = 1;
		if (spl[1][i++] == ',')
			commas_count++;
	}
	if (ft_tablen(rgb_spl) != 3 || is_invalid || commas_count != 2)
	{
		ft_free_tab((void **)spl, -1);
		ft_free_tab((void **)rgb_spl, -1);
		ft_putstr_fd(COLOR_ERR, 2);
		quit(data, 1);
	}
}

/**
 * @brief Gets a color info after checking if it's valid
 *
 * This function splits the color info with commas to get r, g and b values.
 * After checking if the color is valid, we check if the color already existed,
 * in which case there were several occurences of the same identifier, which is
 * invalid. We then convert the rgb value to an int and update the color.
 *
 * @param data Struct object containing all the program data
 * @param color Pointer to the color we're getting
 * @param spl Array of String containing the splitted line
 */
static void	get_color(t_data *data, int *color, char **spl)
{
	char	**rgb_spl;
	int		r;
	int		g;
	int		b;

	rgb_spl = ft_split(spl[1], ',');
	if (!rgb_spl)
		quit(data, 1);
	check_valid_color(data, spl, rgb_spl);
	r = ft_atoi(rgb_spl[0]);
	g = ft_atoi(rgb_spl[1]);
	b = ft_atoi(rgb_spl[2]);
	if (*color != -1 || r < 0 || r > 255 || g < 0 || g > 255
		|| b < 0 || b > 255)
	{
		ft_free_tab((void **)spl, -1);
		ft_free_tab((void **)rgb_spl, -1);
		ft_putstr_fd(COLOR_ERR, 2);
		quit(data, 1);
	}
	ft_free_tab((void **)rgb_spl, -1);
	*color = ft_rgb_to_int(r, g, b);
}

/**
 * @brief Sets the path of an image
 *
 * This function checks if the path of the image already exists. If it does,
 * it means the same identifier was present multiple times, which is invalid.
 * If it doesn't, it sets the path for the image.
 *
 * @param data Struct object containing all the program data
 * @param path Pointer to the path contained in the image in data
 * @param new_path String containing the path to set for the image
 * @param spl Array of String containing the splitted line (to free it if error)
 */
static void	add_path(t_data *data, char **path, char *new_path, char **spl)
{
	if (*path)
	{
		ft_putstr_fd(SCENE_ID_ERR, 2);
		free(new_path);
		ft_free_tab((void **)spl, -1);
		quit(data, 1);
	}
	*path = new_path;
}

/**
 * @brief Checks if an identifier info is valid and stores it
 *
 * This function checks that a received splitted line contains only 2 words:
 * the identifier and the info, and that the identifier is valid. If the info
 * is supposed to be a color, it checks if this color is valid. It then
 * attributes the corresponding info to the right object in the data object.
 *
 * @param data Struct object containing all the program data
 * @param spl Array of String containing the splitted line
 * @return void* Always NULL
 */
static void	*get_info(t_data *data, char **spl)
{
	char	*path;

	if (!spl[1] || spl[2])
		return (ft_putstr_fd(SCENE_ID_ERR, 2),
			ft_free_tab((void **)spl, -1), quit(data, 1), NULL);
	if (ft_strcmp(spl[0], "F") == 0)
		return (get_color(data, &data->floor_color, spl), NULL);
	if (ft_strcmp(spl[0], "C") == 0)
		return (get_color(data, &data->ceil_color, spl), NULL);
	path = ft_strldup(spl[1], -1, '\0');
	if (!path)
		return (ft_free_tab((void **)spl, -1), quit(data, 1), NULL);
	if (ft_strcmp(spl[0], "NO") == 0)
		add_path(data, &data->no->path, path, spl);
	else if (ft_strcmp(spl[0], "SO") == 0)
		add_path(data, &data->so->path, path, spl);
	else if (ft_strcmp(spl[0], "WE") == 0)
		add_path(data, &data->we->path, path, spl);
	else if (ft_strcmp(spl[0], "EA") == 0)
		add_path(data, &data->ea->path, path, spl);
	else
		return (ft_putstr_fd(SCENE_ID_ERR, 2), free(path),
			ft_free_tab((void **)spl, -1), quit(data, 1), NULL);
	return (NULL);
}

/**
 * @brief Checks if a scene is valid
 *
 * This function takes a data object containing the read scene in an array
 * of Strings. It splits each line in words and if the line is not empty,
 * it launches the check for the line identifier and info. If each identifier
 * was seen once, it returns, meaning the scene itself is valid.
 *
 * @param data Struct object containing all the program data
 */
void	check_valid_scene(t_data *data)
{
	char	**spl;

	data->map_start_line = 0;
	while (data->scene[data->map_start_line])
	{
		spl = ft_split(data->scene[(data->map_start_line)++], ' ');
		if (!spl)
			quit(data, 1);
		if (spl[0])
			get_info(data, spl);
		ft_free_tab((void **)spl, -1);
		if (data->ceil_color >= 0 && data->floor_color >= 0 && data->so->path
			&& data->no->path && data->we->path && data->ea->path)
			return ;
	}
	ft_putstr_fd(SCENE_ID_ERR, 2);
	quit(data, 1);
}
