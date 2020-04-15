/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 20:56:27 by admin             #+#    #+#             */
/*   Updated: 2020/04/15 21:49:55 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_left_manual_text(t_sys *system, int *st, int c)
{
	void	*mlx;
	void	*win;
	int		x;
	int		y;

	mlx = system->mlx;
	win = system->win;
	x = st[0];
	y = st[1];
	mlx_string_put(mlx, win, x, y += 30, c, "Rotation");
	mlx_string_put(mlx, win, x + 10, y += 30, c, "LMB & drag - main");
	mlx_string_put(mlx, win, x + 10, y += 30, c, "Z, X - addition");
	mlx_string_put(mlx, win, x, y += 50, c, "Movement");
	mlx_string_put(mlx, win, x + 10, y += 30, c, "RMB & drag");
	mlx_string_put(mlx, win, x, y += 50, c, "Scale");
	mlx_string_put(mlx, win, x + 10, y += 30, c, "MScroll - fast");
	mlx_string_put(mlx, win, x + 10, y += 30, c, "MMB & y_drag - precision");
	mlx_string_put(mlx, win, x, y += 90, c, "Render mode");
}

void	print_left_manual_text_ad(t_sys *system, int *st, int c)
{
	void	*mlx;
	void	*win;
	int		x;
	int		y;

	mlx = system->mlx;
	win = system->win;
	x = st[0];
	y = st[1];
	mlx_string_put(mlx, win, x + 10, y += 360, c, "1 - vertex render");
	mlx_string_put(mlx, win, x + 10, y += 30, c, "2 - wireframe render");
	mlx_string_put(mlx, win, x + 10, y += 30, c, "3 - silhouette render");
	mlx_string_put(mlx, win, x + 10, y += 30, c, "4 - mesh render");
	mlx_string_put(mlx, win, x + 10, y += 30, c, "~ - ON / OFF vertex color");
	mlx_string_put(mlx, win, x + 80, y += 30, c, "(if exists)");
	mlx_string_put(mlx, win, x, y += 90, c, "Projection");
	mlx_string_put(mlx, win, x + 10, y += 30, c,
								"P - perspective/orthographic");
	mlx_string_put(mlx, win, x + 10, y += 70, c, "R - Reset transform");
	mlx_string_put(mlx, win, x + 10, y += 30, c, "F - Focus in center");
	mlx_string_put(mlx, win, x + 20, y += 30, c,
								"(orthographic projection only)");
	mlx_string_put(mlx, win, x, y += 100, c, "ESC - Exit fdf");
}

void	print_right_manual_text(t_setting *s, int *st, t_pb *pb)
{
	pb->x = st[0] + 1570;
	pb->y = st[1];
	pb->number_of_triangles = (s->model.width - 1) * (s->model.height - 1) * 2;
	pb->vertexes = ft_strjoin("number of vertices: ", ft_itoa(s->model.area));
	pb->trianges = ft_strjoin("number of triangles: ",
				ft_itoa(pb->number_of_triangles));
	pb->modelname = ft_strjoin("name: ", s->model.modelname);
	pb->max_x = ft_strjoin("X ", ft_itoa(s->model.width));
	pb->max_y = ft_strjoin("Y ", ft_itoa(s->model.height));
	pb->max_z = ft_strjoin("Z ", ft_itoa(s->model.z_result));
	pb->pivot_x = ft_strjoin("X ",
				ft_itoa((int)s->model.pos[0] - s->model.first_pos[0]));
	pb->pivot_y = ft_strjoin("Y ",
				ft_itoa(-((int)s->model.pos[1] - s->model.first_pos[1])));
}

void	print_right_manual_text_1(t_setting *s, t_pb *pb)
{
	if ((s->model.rot[0]) < 0)
		pb->rot_x = ft_strjoin("X ", ft_itoa(360 + (int)s->model.rot[0]));
	else
		pb->rot_x = ft_strjoin("X ", ft_itoa((int)s->model.rot[0]));
	if ((s->model.rot[1]) < 0)
		pb->rot_y = ft_strjoin("Y ", ft_itoa(360 + (int)s->model.rot[1]));
	else
		pb->rot_y = ft_strjoin("Y ", ft_itoa((int)s->model.rot[1]));
	if ((s->model.rot[2]) < 0)
		pb->rot_z = ft_strjoin("Z ", ft_itoa(360 + (int)s->model.rot[2]));
	else
		pb->rot_z = ft_strjoin("Z ", ft_itoa((int)s->model.rot[2]));
	if (s->model.scale < 0.999999)
		pb->u_s = ft_strjoin("uniform scale: 0", ft_ftoa_an(s->model.scale, 3));
	else
		pb->u_s = ft_strjoin("uniform scale: ", ft_ftoa_an(s->model.scale, 3));
}

void	print_right_manual_text_2(t_setting *s, t_pb *pb)
{
	if ((s->sys.render & 0b0000001))
		pb->rend_mode = ft_strdup("render mode: vertex render");
	else if (s->sys.render & 0b00000010)
		pb->rend_mode = ft_strdup("render mode: wireframe render");
	else if (s->sys.render & 0b00000100)
		pb->rend_mode = ft_strdup("render mode: silhouette render");
	else if (s->sys.render & 0b00001000)
		pb->rend_mode = ft_strdup("render mode: mesh render");
	else
		pb->rend_mode = ft_strdup("render mode unknown");
	if (s->sys.render & 0b01000000)
		pb->color_en = ft_strdup("vertex color: ON");
	else
		pb->color_en = ft_strdup("vertex color: OFF");
	if (s->sys.render & 0b10000000)
		pb->projection = ft_strdup("projection: perspective");
	else
		pb->projection = ft_strdup("projection: orthographic");
}
