/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:52:09 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/11/05 10:56:18 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	get_first_point(t_game *game, int curr_sector,
		t_vec2 *first_point, int i)
{
	*first_point = *(game->points_cam + *((game->sectors +
					curr_sector)->index_points + i));
	first_point->x = first_point->x * 20 + game->pre_calc.screen_w_div_20;
	first_point->y = -first_point->y * 20 + game->pre_calc.screen_h_div_20;
}

void	get_second_point(t_game *game, int curr_sector,
		t_vec2 *second_point, int i)
{
	if (i == (game->sectors + curr_sector)->count_wall - 1)
		*second_point = *(game->points_cam + *((game->sectors +
		curr_sector)->index_points));
	else
		*second_point = *(game->points_cam + *((game->sectors +
		curr_sector)->index_points + i + 1));
	second_point->x = second_point->x * 20 + game->pre_calc.screen_w_div_20;
	second_point->y = -second_point->y * 20 + game->pre_calc.screen_h_div_20;
}

void			swap_vec2(t_vec2 *first, t_vec2 *second)
{
	double	swap;

	swap = first->x;
	first->x = second->x;
	second->x = swap;
	swap = first->y;
	first->y = second->y;
	second->y = swap;
}
