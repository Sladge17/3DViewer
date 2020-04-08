/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 10:31:42 by student           #+#    #+#             */
/*   Updated: 2020/04/08 10:31:45 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	transform_model(t_system *system, t_model *model, t_coords *coords)
{
	int		k;

	if (draw_zeroscale(system, model))
		return ;
	coords->counter[1] = 0;
	while (coords->counter[1] < model->height - 1)
	{
		coords->counter[0] = 0;
		while (coords->counter[0] < model->width - 1)
		{
			setup_quad(model, coords, &k);
			while (k < 4)
			{
				transform_quad(system, model, coords, k);
				k += 1;
			}
			draw_model(system, model, coords);
			coords->counter[0] += 1;
		}
		coords->counter[1] += 1;
	}
}

char	draw_zeroscale(t_system *system, t_model *model)
{
	if (model->scale)
		return (0);
	if (model->color_f && system->render & 64)
	{
		system->output[model->pos[0] + model->pos[1] * WIDTH] =
			model->vertex[model->area / 2][3];
		return (1);
	}
	if (system->render & 12)
	{
		system->output[model->pos[0] + model->pos[1] * WIDTH] = COLOR_S;
		return (1);
	}
	if (system->render & 2)
	{
		system->output[model->pos[0] + model->pos[1] * WIDTH] = COLOR_W;
		return (1);
	}
	system->output[model->pos[0] + model->pos[1] * WIDTH] = COLOR_V;
	return (1);
}

void	transform_quad(t_system *system, t_model *model, t_coords *coords, int k)
{
	rotate_quad(model, coords, k);
	if (system->render & 128)
		persp_distortion(model, coords, k);
	scale_quad(model, coords, k);
	move_quad(model, coords, k);
	round_quad(model, coords, k);
}

char	vertz_zbuf(t_system *system, t_coords *coords)
{
	if (coords->d_tris[0][0] != coords->d_tris[1][0] ||
		coords->d_tris[0][1] != coords->d_tris[1][1])
		return (0);
	if ((0 <= coords->d_tris[0][0] && coords->d_tris[0][0] < WIDTH) &&
		(0 <= coords->d_tris[0][1] && coords->d_tris[0][1] < HEIGHT) &&
		coords->f_tris[0] > coords->f_tris[1] &&
		((int)coords->f_tris[0] > system->z_buf[coords->d_tris[0][0] +
		coords->d_tris[0][1] * WIDTH]))
	{
		system->output[coords->d_tris[0][0] +
		coords->d_tris[0][1] * WIDTH] = coords->d_tris[0][2];
		system->z_buf[coords->d_tris[0][0] +
		coords->d_tris[0][1] * WIDTH] = coords->f_tris[0];
	}
	return (1);
}

