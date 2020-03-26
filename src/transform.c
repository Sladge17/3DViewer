/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 19:26:21 by jthuy             #+#    #+#             */
/*   Updated: 2020/03/23 17:32:17 by student          ###   ########.fr       */
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
				rotate_quad(model, coords, k);
				if (system->render & 128)
					persp_distortion(model, coords, k);
				scale_quad(model, coords, k);
				move_quad(model, coords, k);
				round_quad(model, coords, k);
				k += 1;
			}
			draw_model(system, model, coords);
			// draw_qvertex(system, model, coords);
			coords->counter[0] += 1;
		}
		coords->counter[1] += 1;
	}
}

void	rotate_quad(t_model *model, t_coords *coords, int k)
{
	coords->tmp[0] = model->vertex[coords->index[k]][0];
	coords->tmp[1] = model->vertex[coords->index[k]][1];
	coords->tmp[2] = model->vertex[coords->index[k]][2];
	coords->f_quad[k][1] = coords->tmp[1] * cos((model->rot[0] * M_PI) / 180)
						+ coords->tmp[2] * sin((model->rot[0] * M_PI) / 180);
	coords->f_quad[k][2] = -coords->tmp[1] * sin((model->rot[0] * M_PI) / 180)
						+ coords->tmp[2] * cos((model->rot[0] * M_PI) / 180);
	coords->tmp[1] = coords->f_quad[k][1];
	coords->tmp[2] = coords->f_quad[k][2];
	coords->f_quad[k][0] = coords->tmp[0] * cos((model->rot[1] * M_PI) / 180)
						+ coords->tmp[2] * sin((model->rot[1] * M_PI) / 180);
	coords->f_quad[k][2] = -coords->tmp[0] * sin((model->rot[1] * M_PI) / 180)
						+ coords->tmp[2] * cos((model->rot[1] * M_PI) / 180);
	coords->tmp[0] = coords->f_quad[k][0];
	coords->tmp[2] = coords->f_quad[k][2];
	coords->f_quad[k][0] = coords->tmp[0] * cos((model->rot[2] * M_PI) / 180)
						- coords->tmp[1] * sin((model->rot[2] * M_PI) / 180);
	coords->f_quad[k][1] = coords->tmp[0] * sin((model->rot[2] * M_PI) / 180)
						+ coords->tmp[1] * cos((model->rot[2] * M_PI) / 180);
}

void	persp_distortion(t_model *model, t_coords *coords, int k)
{
	int		z_offset = 100;
	int		fov = 90;
	z_offset = 1000 * tan(fov * 0.5 * M_PI / 180);
	
	coords->tmp[0] = coords->f_quad[k][0] - (WIDTH / 2 - model->pos[0]);
	coords->tmp[1] = coords->f_quad[k][1] - (HEIGHT / 2 - model->pos[1]);
	coords->tmp[2] = coords->f_quad[k][2];

	coords->f_quad[k][0] = coords->tmp[0] / (1 - coords->tmp[2] / z_offset);
	coords->f_quad[k][1] = coords->tmp[1] / (1 - coords->tmp[2] / z_offset);
	coords->f_quad[k][2] = coords->tmp[2] / (1 - coords->tmp[2] / z_offset);

	coords->f_quad[k][0] += WIDTH / 2 - model->pos[0];
	coords->f_quad[k][1] += HEIGHT / 2 - model->pos[1];
	coords->f_quad[k][2] = coords->f_quad[k][2];
}

void	scale_quad(t_model *model, t_coords *coords, int k)
{
	coords->f_quad[k][0] *= model->scale;
	coords->f_quad[k][1] *= model->scale;
	coords->f_quad[k][2] *= model->scale;
}

void	move_quad(t_model *model, t_coords *coords, int k)
{
	coords->f_quad[k][0] += model->pos[0];
	coords->f_quad[k][1] += model->pos[1];
}

void	round_quad(t_model *model, t_coords *coords, int k)
{
	coords->d_quad[k][0] = lround(coords->f_quad[k][0]);
	coords->d_quad[k][1] = lround(coords->f_quad[k][1]);
	coords->d_quad[k][2] = model->vertex[coords->index[k]][3];
}

