/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 10:18:41 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/03/29 10:22:04 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"


static double   cross_product(double x1, double y1, double x2, double y2)
{
	return (x1 * y2 - x2 * y1);
}

static void     cross(double *x1, double *y1, double x2, double y2, double x_fov, double y_fov)
{
	double new_x;
	double new_y;
	double det;

	det = cross_product(*x1, *y1, x2, y2) / ((-x_fov) * (*y1 - y2) + y_fov * (*x1 - x2));
	new_x = x_fov * det;
	new_y = y_fov * det;
	*x1 = new_x;
	*y1 = new_y;
}

int             intersection(double *x1, double *y1, double *x2, double *y2)
{
	double x1_fov;
	double x2_fov;
	double y1_fov;
	double y2_fov;
	double x;
	double y;

	x1_fov = 8.66;
	y1_fov = 5;
	x2_fov = 8.66;
	y2_fov = -5;
	x = cross_product(x1_fov, y1_fov, *x1, *y1);
	y = cross_product(x1_fov, y1_fov, *x2, *y2);
	if (x > 0 && y > 0)
		return (0);
	if (x > 0 || y > 0)
	{
		if (x > 0)
			cross(x1, y1, *x2, *y2, x1_fov, y1_fov);
		else
			cross(x2, y2, *x1, *y1, x1_fov, y1_fov);
	}
	x = cross_product(x2_fov, y2_fov, *x1, *y1);
	y = cross_product(x2_fov, y2_fov, *x2, *y2);
	if (x < 0 && y < 0)
		return (0);
	if (x < 0 || y < 0)
	{
		if (x < 0)
			cross(x1, y1, *x2, *y2, x2_fov, y2_fov);
		else
			cross(x2, y2, *x1, *y1, x2_fov, y2_fov);
	}
	return (1);
}
