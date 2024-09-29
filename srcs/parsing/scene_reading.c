/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_reading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:00:38 by mrochedy          #+#    #+#             */
/*   Updated: 2024/08/30 15:53:46 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_empty_scene(t_data *data)
{
	int	i;

	i = 0;
	while (data->scene[i])
		if (data->scene[i++][0])
			return ;
	ft_putstr_fd(EMPTY_SCENE_ERR, 2);
	quit(data, 1);
}

/**
 * @brief Reads and adds one line to the scene
 *
 * This function reallocates the scene, which is an array of String, to
 * contain one more line. It then reads the next line of the file to add
 * it to the scene and replaces the '\n' with a '\0'.
 *
 * @param data Struct object containing all the program data
 * @param scene Pointer to the array of String containing the scene
 * @param i The index of the current line
 * @param fd The file descriptor of the scene file
 */
static void	add_one_line(t_data *data, char ***scene, int i, int fd)
{
	char	**tmp;
	int		line_len;

	tmp = ft_realloc(*scene, sizeof(char *) * (i + 1),
			sizeof(char *) * (i + 1 + 2));
	if (!tmp)
	{
		close(fd);
		quit(data, 1);
	}
	*scene = tmp;
	(*scene)[i + 1] = get_next_line(fd);
	if ((*scene)[i + 1])
	{
		line_len = ft_strlen((*scene)[i + 1]);
		if (line_len > 0 && (*scene)[i + 1][line_len - 1] == '\n')
			(*scene)[i + 1][line_len - 1] = '\0';
	}
}

/**
 * @brief Reads the scene file and stores the scene in the data object
 *
 * This function opens the scene file, and reads it and stores it line by
 * line. It replaces the '\n' at the end of each line with a '\0'.
 * It then checks if the scene is valid.
 *
 * @param data Struct object containing all the program data
 * @param file String containing the scene file path
 */
void	*read_scene(t_data *data, char *file)
{
	int		fd;
	int		i;
	int		line_len;
	char	**scene;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd(SCENE_FILE_ERR, 2), quit(data, 1), NULL);
	scene = malloc(sizeof(char *));
	if (!scene)
		return (close(fd), quit(data, 1), NULL);
	i = 0;
	scene[i] = get_next_line(fd);
	if (!scene[i])
		return (close(fd), free(scene), ft_putstr_fd(EMPTY_SCENE_ERR, 2),
			quit(data, 1), NULL);
	line_len = ft_strlen(scene[i]);
	if (line_len > 0 && scene[i][line_len - 1] == '\n')
		scene[i][line_len - 1] = '\0';
	while (scene[i])
		add_one_line(data, &scene, i++, fd);
	data->scene = scene;
	return (close(fd), check_empty_scene(data), check_valid_scene(data), NULL);
}
