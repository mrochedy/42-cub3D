/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdaher <hdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:45:13 by mrochedy          #+#    #+#             */
/*   Updated: 2024/08/29 18:20:18 by hdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define BUFFER_SIZE 42

static char	*conc_strings(char *str, char *buffer)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = malloc((ft_strlen(str) + ft_strlen(buffer) + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	while (str && str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	while (buffer && buffer[j])
	{
		new_str[i + j] = buffer[j];
		j++;
	}
	new_str[i + j] = '\0';
	ft_strdel(&str);
	return (new_str);
}

static int	is_new_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

static char	*delete_first_chars(char *str, int n)
{
	char	*new_str;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(str);
	new_str = malloc((len - n + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	while (i < len - n)
	{
		new_str[i] = str[n + i];
		i++;
	}
	new_str[i] = '\0';
	ft_strdel(&str);
	return (new_str);
}

static char	*select_line(char **strptr)
{
	int		i;
	int		len;
	char	*selected_line;
	char	*str;

	i = 0;
	str = *strptr;
	len = is_new_line(str);
	if (!len)
		len = ft_strlen(str);
	selected_line = malloc((len + 1) * sizeof(char));
	if (!selected_line)
		return (NULL);
	while (str && str[i] && str[i] != '\n')
	{
		selected_line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		selected_line[i++] = '\n';
	selected_line[i] = '\0';
	*strptr = delete_first_chars(*strptr, i);
	return (selected_line);
}

char	*get_next_line(int fd)
{
	static char	*str = NULL;
	char		*buffer;
	int			ret;

	if ((str && *str) && is_new_line(str))
		return (select_line(&str));
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer || BUFFER_SIZE < 0)
		return (ft_strdel(&buffer), NULL);
	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret == 0 && (!str))
			break ;
		else if (ret < 0)
			return (ft_strdel(&buffer), ft_strdel(&str), NULL);
		buffer[ret] = '\0';
		str = conc_strings(str, buffer);
		if (is_new_line(str))
			break ;
	}
	if ((ret == 0 && (!str || *str == '\0')))
		return (ft_strdel(&str), ft_strdel(&buffer), NULL);
	return (ft_strdel(&buffer), select_line(&str));
}
