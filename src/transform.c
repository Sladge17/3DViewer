/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 16:27:48 by jthuy             #+#    #+#             */
/*   Updated: 2020/03/16 16:37:19 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	transform_model(t_system *system, t_model *model, t_coords *coords)
{
	int		k;

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
				if (!model->overall)
				{
					model->rot_vertex[coords->index[k]][0] = lround(coords->f_quad[k][0]);
					model->rot_vertex[coords->index[k]][1] = lround(coords->f_quad[k][1]);
					k += 1;
					continue ;
				}
				scale_quad(model, coords, k);
				move_quad(model, coords, k);
				round_quad(coords, k);
				k += 1;
			}
			if (!model->overall)
			{
				coords->counter[0] += 1;
				continue ;
			}
			draw_model(system, model, coords);
			coords->counter[0] += 1;
		}
		coords->counter[1] += 1;
	}
	if (!model->overall)
	{
		set_scale(model);
		transform_model(system, model, coords);
	}
}

void	set_scale(t_model *model)
{
	static char	first = 0;
	int			vert_min[2];
	int			vert_max[2];
	int			o_len[2];
	int			i;


	vert_min[0] = model->rot_vertex[0][0];
	vert_min[1] = model->rot_vertex[0][1];
	vert_max[0] = model->rot_vertex[0][0];
	vert_max[1] = model->rot_vertex[0][1];
	i = 1;
	while (i < model->area)
	{
		vert_min[0] = model->rot_vertex[i][0] < vert_min[0] ? model->rot_vertex[i][0] : vert_min[0];
		vert_min[1] = model->rot_vertex[i][1] < vert_min[1] ? model->rot_vertex[i][1] : vert_min[1];
		vert_max[0] = model->rot_vertex[i][0] > vert_max[0] ? model->rot_vertex[i][0] : vert_max[0];
		vert_max[1] = model->rot_vertex[i][1] > vert_max[1] ? model->rot_vertex[i][1] : vert_max[1];
		i += 1;
	}
	
	o_len[0] = vert_max[0] - vert_min[0];
	o_len[1] = vert_max[1] - vert_min[1];

	model->scale = WIDTH / o_len[0] < HEIGHT / o_len[1] ? (float)(WIDTH - 100) / (float)o_len[0] : (float)(HEIGHT - 100) / (float)o_len[1];
	model->pos[0] = WIDTH / 2 - model->scale * (vert_min[0] + o_len[0] / 2);
	model->pos[1] = HEIGHT / 2 - model->scale * (vert_min[1] + o_len[1] / 2);
	model->overall = 1;
	
	if (!first)
	{
		model->first_scale = model->scale;
		model->first_pos[0] = model->pos[0];
		model->first_pos[1] = model->pos[1];
		first = 1;
	}

	
}




void	setup_quad(t_model *model, t_coords *coords, int *k)
{
	if (!coords->counter[0])
	{
		*k = 0;
		coords->index[0] = coords->counter[0] + coords->counter[1] * model->width;
		coords->index[1] = coords->counter[0] + model->width
						+ coords->counter[1] * model->width;
	}
	else
	{
		*k = 2;
		coords->f_quad[0][0] = coords->f_quad[2][0];
		coords->f_quad[0][1] = coords->f_quad[2][1];
		coords->f_quad[0][2] = coords->f_quad[2][2];

		coords->f_quad[1][0] = coords->f_quad[3][0];
		coords->f_quad[1][1] = coords->f_quad[3][1];
		coords->f_quad[1][2] = coords->f_quad[3][2];
		
		coords->d_quad[0][0] = coords->d_quad[2][0];
		coords->d_quad[0][1] = coords->d_quad[2][1];
		coords->d_quad[1][0] = coords->d_quad[3][0];
		coords->d_quad[1][1] = coords->d_quad[3][1];
	}
	coords->index[2] = coords->counter[0] + coords->counter[1] * model->width + 1;
	coords->index[3] = coords->counter[0] + model->width
					+ coords->counter[1] * model->width + 1;


	// *k = 0;
	// coords->index[0] = coords->counter[0] + coords->counter[1] * model->width;
	// coords->index[1] = coords->counter[0] + model->width
	// 					+ coords->counter[1] * model->width;
	// coords->index[2] = coords->counter[0] + coords->counter[1] * model->width + 1;
	// coords->index[3] = coords->counter[0] + model->width
	// 				+ coords->counter[1] * model->width + 1;
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
	int	z_offset = 100;
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

void	round_quad(t_coords *coords, int k)
{
	coords->d_quad[k][0] = lround(coords->f_quad[k][0]);
	coords->d_quad[k][1] = lround(coords->f_quad[k][1]);
}