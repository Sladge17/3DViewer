/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_model.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 18:44:15 by student           #+#    #+#             */
/*   Updated: 2020/04/07 18:44:19 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_diagonal(t_model *model)
{
	float	diag03;
	float	diag12;
	int		i;
	int		j;

	if (!(model->diagonal = (char *)malloc(sizeof(char) *
			((model->width - 1) * (model->height - 1)))))
		exit(0);
	j = 0;
	while (j < model->height - 1)
	{
		i = 0;
		while (i < model->width - 1)
		{
			diag03 = len_diag(model->vertex[i + j * model->width],
				model->vertex[i + model->width + 1 + j * model->width]);
			diag12 = len_diag(model->vertex[i + 1 + j * model->width],
				model->vertex[i + model->width + j * model->width]);
			model->diagonal[i + j * (model->width - 1)] =
				diag12 > diag03 ? 0 : 1;
			i += 1;
		}
		j += 1;
	}
}

float	len_diag(int *vertex_0, int *vertex_1)
{
	float	lenght;
	int		len[3];

	len[0] = abs(vertex_1[0] - vertex_0[0]);
	len[1] = abs(vertex_1[1] - vertex_0[1]);
	len[2] = abs(vertex_1[2] - vertex_0[2]);
	lenght = sqrt(len[0] * len[0] + len[1] * len[1] + len[2] * len[2]);
	return (lenght);
}

void	pre_transform(t_model *model)
{
	int		i;
	int		shift[2];

	shift[0] = model->vertex[model->area - 1][0];
	shift[1] = model->vertex[model->area - 1][1];
	i = 0;
	while (i < model->area)
	{
		model->vertex[i][0] *= 2;
		model->vertex[i][0] -= shift[0];
		model->vertex[i][1] *= 2;
		model->vertex[i][1] -= shift[1];
		model->vertex[i][2] *= 2;
		i += 1;
	}
}

void	set_overall(t_model *model)
{
	int		i;

	if (!(model->o_vertex = (float **)malloc(sizeof(float *) * model->area)))
		exit(0);
	i = 0;
	while (i < model->area)
	{
		if (!(model->o_vertex[i] = (float *)malloc(sizeof(float) * 2)))
			exit(0);
		i += 1;
	}
}
