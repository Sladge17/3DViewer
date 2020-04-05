/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_silhouette_z.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 12:38:40 by student           #+#    #+#             */
/*   Updated: 2020/04/01 12:38:51 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fquad_zbuf(t_system *system, t_model *model, t_coords *coords)
{
	if ((coords->d_quad[0][0] == coords->d_quad[1][0] &&
		coords->d_quad[1][0] == coords->d_quad[2][0] &&
		coords->d_quad[2][0] == coords->d_quad[3][0]) ||
		(coords->d_quad[0][1] == coords->d_quad[1][1] &&
		coords->d_quad[1][1] == coords->d_quad[2][1] &&
		coords->d_quad[2][1] == coords->d_quad[3][1]))
	{
		quad_zbuf(system, model, coords);
		return ;
	}
	if (model->diagonal[coords->counter[0] +
		coords->counter[1] * (model->width - 1)])
	{
		deftris_zbuf(coords, 0, 1, 3);
		ftris_zbuf(system, coords);
		deftris_zbuf(coords, 0, 2, 3);
		ftris_zbuf(system, coords);
		return ;
	}
	deftris_zbuf(coords, 0, 1, 2);
	ftris_zbuf(system, coords);
	deftris_zbuf(coords, 1, 2, 3);
	ftris_zbuf(system, coords);
}

void	deftris_zbuf(t_coords *coords, char v1, char v2, char v3)
{
	coords->d_tris[0][0] = coords->d_quad[v1][0];
	coords->d_tris[0][1] = coords->d_quad[v1][1];
	coords->d_tris[0][2] = coords->d_quad[v1][2];
	coords->f_tris[0] = coords->f_quad[v1][2];
	coords->d_tris[1][0] = coords->d_quad[v2][0];
	coords->d_tris[1][1] = coords->d_quad[v2][1];
	coords->d_tris[1][2] = coords->d_quad[v2][2];
	coords->f_tris[1] = coords->f_quad[v2][2];
	coords->d_tris[2][0] = coords->d_quad[v3][0];
	coords->d_tris[2][1] = coords->d_quad[v3][1];
	coords->d_tris[2][2] = coords->d_quad[v3][2];
	coords->f_tris[2] = coords->f_quad[v3][2];
}

void	ftris_zbuf(t_system *system, t_coords *coords)	
{
	int		segment_height;
	int		total_height;
	int		i;
	float	int_x1;
	float	int_x2;

	// static char	flag = 1;

	// int		coords->d_line[0][1];
	// int		coords->d_line[0][0];
	// int		coords->d_line[1][0];

	// int		coords->d_line[0][2];
	// int		coords->d_line[1][2];

	// int		coords->d_line[0][3];
	// int		coords->d_line[1][3];

	// float	z1;
	// float	z2;
	// float	cur_z[3];

	sorty_zbuf(coords);


	total_height = coords->d_tris[2][1] - coords->d_tris[0][1];
	coords->d_line[0][1] = coords->d_tris[0][1];
	// coords->d_line[1][1] = coords->d_tris[0][1];

	// i = 0;

	// if (coords->d_tris[0][1] == coords->d_tris[1][1])
	// 	i = 1;

	i = coords->d_tris[0][1] == coords->d_tris[1][1] ? 1 : 0;

	while (i < 2)
	{
		segment_height = coords->d_tris[i + 1][1] - coords->d_tris[i][1];
		while (coords->d_line[0][1] < coords->d_tris[i + 1][1])
		{
			coords->d_line[1][1] = coords->d_line[0][1];

			int_x1 = (float)(coords->d_line[0][1] - coords->d_tris[0][1]) / total_height;
			int_x2 = (float)(coords->d_line[0][1] - coords->d_tris[i][1]) / segment_height;
			coords->d_line[0][0] = coords->d_tris[0][0] + (coords->d_tris[2][0] - coords->d_tris[0][0]) * int_x1;
			coords->d_line[1][0] = coords->d_tris[i][0] + (coords->d_tris[i + 1][0] - coords->d_tris[i][0]) * int_x2;

			
			if (system->render & 64)
			{
				coords->d_line[0][2] = set_yrgb(coords->d_tris[0], coords->d_tris[2], coords->d_line[0][1]);
				coords->d_line[1][2] = set_yrgb(coords->d_tris[i], coords->d_tris[i + 1], coords->d_line[0][1]);
			}

			coords->f_line[0] = coords->f_tris[0] + (coords->f_tris[2] - coords->f_tris[0]) * int_x1;
			coords->f_line[1] = coords->f_tris[i] + (coords->f_tris[i + 1] - coords->f_tris[i]) * int_x2;

			// coords->d_line[0][0] = coords->d_line[0][0];
			// coords->d_line[0][1] = coords->d_line[0][1];
			// coords->d_line[0][2] = coords->d_line[0][2];

			// coords->d_line[1][0] = coords->d_line[1][0];
			// coords->d_line[1][1] = coords->d_line[0][1];
			// coords->d_line[1][2] = coords->d_line[1][2];

			// cur_z[0] = z1;
			// cur_z[1] = z2;
			// cur_z[2] = coords->f_line[2];


			// linex_zbuf(system, coords->d_line[0], coords->d_line[1], cur_z);

			linex_zbuf(system, coords->d_line[0], coords->d_line[1], coords->f_line);

			// if (!flag)
			// {
				if ((0 <= coords->d_line[1][0] && coords->d_line[1][0] < WIDTH) &&
					(0 <= coords->d_line[1][1] && coords->d_line[1][1] < HEIGHT) &&
					(int)coords->f_line[1] >= system->z_buf[coords->d_line[1][0] + coords->d_line[1][1] * WIDTH])
				{
					

					// if ((system->render & 72) == 72)
					if ((system->render & 8) && (system->render & 64))
					{
						system->output[coords->d_line[1][0] +
						coords->d_line[1][1] * WIDTH] = shade_lastpix(coords, coords->d_line[1][2]);
					}
					else
					{
						system->output[coords->d_line[1][0] +
						coords->d_line[1][1] * WIDTH] = coords->d_line[1][2];
					}

					// system->output[coords->d_line[1][0] +
					// coords->d_line[1][1] * WIDTH] = shade_lastpix(coords, coords->d_line[1][2]);

					system->z_buf[coords->d_line[1][0] + coords->d_line[1][1] * WIDTH] = (int)coords->f_line[1];
				}
			// }
			// flag ^= 1;

			coords->d_line[0][1] += 1;
			// coords->d_line[1][1] += 1;

		}
		if (coords->d_tris[1][1] == coords->d_tris[2][1])
			break ;
		i += 1;
	}
}


int		shade_lastpix(t_coords *coords, int color)
{
	unsigned char	rgb[3];
	
	rgb[0] = (color & (255 << 16)) >> 16;
	rgb[1] = (color & (255 << 8)) >> 8;
	rgb[2] = color & 255;
	// color = lround(lightpower * rgb[0]) +
	// 		(lround(lightpower * rgb[1]) << 8) +
	// 		(lround(lightpower * rgb[2]) << 16);
	color = (lround(coords->f_line[2] * rgb[0]) << 16) +
			(lround(coords->f_line[2] * rgb[1]) << 8) +
			lround(coords->f_line[2] * rgb[2]);
	return (color);
}





void	sorty_zbuf(t_coords *coords)
{
	int		i;
	int		j;
	int		tmp_d;
	float	tmp_f;

	j = 0;
	while (j < 2)
	{
		i = 0;
		while (i < 2 - j)
		{
			if (coords->d_tris[i][1] > coords->d_tris[i + 1][1])
			{
				tmp_d = coords->d_tris[i][0];
				coords->d_tris[i][0] = coords->d_tris[i + 1][0];
				coords->d_tris[i + 1][0] = tmp_d;
				tmp_d = coords->d_tris[i][1];
				coords->d_tris[i][1] = coords->d_tris[i + 1][1];
				coords->d_tris[i + 1][1] = tmp_d;
				tmp_d = coords->d_tris[i][2];
				coords->d_tris[i][2] = coords->d_tris[i + 1][2];
				coords->d_tris[i + 1][2] = tmp_d;
				tmp_f = coords->f_tris[i];
				coords->f_tris[i] = coords->f_tris[i + 1];
				coords->f_tris[i + 1] = tmp_f;
			}
			i += 1;
		}
		j += 1;
	}
}

