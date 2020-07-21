/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 21:49:20 by admin             #+#    #+#             */
/*   Updated: 2020/07/21 17:50:31 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_right_manual_text_a(t_setting *s, int c, t_pb *pb)
{
	void	*mlx;
	void	*win;

	mlx = s->sys.mlx;
	win = s->sys.win;
	mlx_string_put(mlx, win, pb->x, pb->y += 30, c, "Model");
	mlx_string_put(mlx, win, pb->x + 10, pb->y += 30, c, pb->modelname);
	mlx_string_put(mlx, win, pb->x + 10, pb->y += 30, c, "overal dimensions:");
	mlx_string_put(mlx, win, pb->x + 20, pb->y += 30, c, pb->max_x);
	mlx_string_put(mlx, win, pb->x + 20, pb->y += 30, c, pb->max_y);
	mlx_string_put(mlx, win, pb->x + 20, pb->y += 30, c, pb->max_z);
	mlx_string_put(mlx, win, pb->x + 10, pb->y += 30, c, pb->vertexes);
	mlx_string_put(mlx, win, pb->x + 10, pb->y += 30, c, pb->trianges);
	if (s->model.color_f)
	{
		mlx_string_put(mlx, win, pb->x + 10, pb->y += 30, c,
									"vertex color: YES");
	}
	else
	{
		mlx_string_put(mlx, win, pb->x + 10, pb->y += 30, c,
					"vertex color: NO");
	}
}

void	print_right_manual_text_ad(t_setting *s, int c, t_pb *pb)
{
	void *mlx;
	void *win;

	mlx = s->sys.mlx;
	win = s->sys.win;
	mlx_string_put(mlx, win, pb->x, pb->y += 50, c, "Pivot");
	mlx_string_put(mlx, win, pb->x + 10, pb->y += 30, c, "position:");
	mlx_string_put(mlx, win, pb->x + 20, pb->y += 30, c, pb->pivot_x);
	mlx_string_put(mlx, win, pb->x + 20, pb->y += 30, c, pb->pivot_y);
	mlx_string_put(mlx, win, pb->x + 10, pb->y += 40, c, "rotation");
	mlx_string_put(mlx, win, pb->x + 20, pb->y += 30, c, pb->rot_x);
	mlx_string_put(mlx, win, pb->x + 20, pb->y += 30, c, pb->rot_y);
	mlx_string_put(mlx, win, pb->x + 20, pb->y += 30, c, pb->rot_z);
	mlx_string_put(mlx, win, pb->x + 20, pb->y += 30, c, pb->u_s);
	mlx_string_put(mlx, win, pb->x, pb->y += 50, c, "Scene");
	mlx_string_put(mlx, win, pb->x + 10, pb->y += 30, c, pb->rend_mode);
	mlx_string_put(mlx, win, pb->x + 10, pb->y += 30, c, pb->color_en);
	mlx_string_put(mlx, win, pb->x + 10, pb->y += 30, c, pb->projection);
}

void free_pb(t_pb **pbb)
{
	t_pb *pb = *pbb;
	free(pb->vertexes);
	free(pb->trianges);
	free(pb->modelname);
	free(pb->max_x);
	free(pb->max_y);
	free(pb->max_z);

	free(pb->pivot_x);
	free(pb->pivot_y);
	free(pb->rot_x);
	free(pb->rot_y);
	free(pb->rot_z);
	free(pb->u_s);
	free(pb->rend_mode);
	free(pb->color_en);
	free(pb->projection);
	ft_printf("here");
	if (pb)
		free(pb);

}

void	print_left_text(t_setting *setting, int c)
{
	int start[2];

	start[0] = 20;
	start[1] = 20;
	print_left_manual_text(&setting->sys, start, c);
	print_left_manual_text_ad(&setting->sys, start, c);
}

void	print_right_text(t_setting *setting, int c)
{
	t_pb	*pb;
	int		start[2];

	start[0] = 15;
	start[1] = 20;
	pb = (t_pb *)malloc(sizeof(t_pb));
	print_right_manual_text(setting, start, pb);
	print_right_manual_text_1(setting, pb);
	print_right_manual_text_2(setting, pb);
	print_right_manual_text_a(setting, c, pb);
	print_right_manual_text_ad(setting, c, pb);
	free_pb(&pb);
	//free(pb);
}

void	print_two_small_buttons_text(t_setting *setting, int c)
{
	mlx_string_put(setting->sys.mlx, setting->sys.win, 1745, 1042, c,
										"I - Information");
	mlx_string_put(setting->sys.mlx, setting->sys.win, 35, 1045, c,
										"C - Controls");
}
