/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 10:31:42 by student           #+#    #+#             */
/*   Updated: 2020/04/10 16:53:13 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	transform_model(t_sys *sys, t_model *model, t_coords *coords)
{
	int		k;

	if (draw_zeroscale(sys, model))
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
				transform_quad(sys, model, coords, k);
				k += 1;
			}
			draw_model(sys, model, coords);
			coords->counter[0] += 1;
		}
		coords->counter[1] += 1;
	}
}

char	draw_zeroscale(t_sys *sys, t_model *model)
{
	if (model->scale)
		return (0);
	if (model->color_f && sys->render & 64)
	{
		sys->output[model->pos[0] + model->pos[1] * WIDTH] =
			model->vertex[model->area / 2][3];
		return (1);
	}
	if (sys->render & 12)
	{
		sys->output[model->pos[0] + model->pos[1] * WIDTH] = COLOR_S;
		return (1);
	}
	if (sys->render & 2)
	{
		sys->output[model->pos[0] + model->pos[1] * WIDTH] = COLOR_W;
		return (1);
	}
	sys->output[model->pos[0] + model->pos[1] * WIDTH] = COLOR_V;
	return (1);
}

void	transform_quad(t_sys *sys, t_model *model, t_coords *coords, int k)
{
	rotate_quad(model, coords, k);
	if (sys->render & 128)
		persp_distortion(model, coords, k);
	scale_quad(model, coords, k);
	move_quad(model, coords, k);
	round_quad(model, coords, k);
}

char	vertz_zbuf(t_sys *sys, t_coords *coords)
{
	if (coords->d_tris[0][0] != coords->d_tris[1][0] ||
		coords->d_tris[0][1] != coords->d_tris[1][1])
		return (0);
	if ((0 <= coords->d_tris[0][0] && coords->d_tris[0][0] < WIDTH) &&
		(0 <= coords->d_tris[0][1] && coords->d_tris[0][1] < HEIGHT) &&
		coords->f_tris[0] > coords->f_tris[1] &&
		((int)coords->f_tris[0] > sys->z_buf[coords->d_tris[0][0] +
		coords->d_tris[0][1] * WIDTH]))
	{
		sys->output[coords->d_tris[0][0] +
		coords->d_tris[0][1] * WIDTH] = coords->d_tris[0][2];
		sys->z_buf[coords->d_tris[0][0] +
		coords->d_tris[0][1] * WIDTH] = coords->f_tris[0];
	}
	return (1);
}
