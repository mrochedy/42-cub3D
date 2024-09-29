/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_distance_to.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdaher <hdaher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:53:50 by hdaher            #+#    #+#             */
/*   Updated: 2024/09/03 18:24:42 by hdaher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief This function calculates the distance between two points
 *
 * This function calculates the distance between the two points of
 * coordinates (x1, y1), (x2, y2) using the mathematic formula.
 *
 * @param data Pointer to the t_data structure containing all data
 * @return double: Distance between the points
 */
double	ft_distance_to(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}
