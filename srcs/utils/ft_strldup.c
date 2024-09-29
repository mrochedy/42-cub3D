/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochedy <mrochedy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:49:05 by hdaher            #+#    #+#             */
/*   Updated: 2024/08/30 16:24:31 by mrochedy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strldup(const char *s, int len, char c)
{
	char	*str;
	int		i;
	int		size;

	if (!s)
		return (NULL);
	i = 0;
	size = 0;
	while (s[size])
		size++;
	if (len > size)
		str = malloc((len + 1) * sizeof(char));
	else
		str = malloc((size + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i < size)
	{
		str[i] = s[i];
		i++;
	}
	while (i < len)
		str[i++] = c;
	str[i] = '\0';
	return (str);
}
