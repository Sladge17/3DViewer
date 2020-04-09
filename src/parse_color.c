/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 16:33:37 by student           #+#    #+#             */
/*   Updated: 2020/04/08 16:33:43 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		set_xrgb(int *vertex_0, int *vertex_1, int cursor)
{
	unsigned char	*rgb[2];
	char			d_rgb[3];
	unsigned char	len[3];
	float			int_color;
	int				color;

	rgb[0] = (unsigned char *)&vertex_0[2];
	rgb[1] = (unsigned char *)&vertex_1[2];
	d_rgb[0] = rgb[1][0] > rgb[0][0] ? 1 : -1;
	d_rgb[1] = rgb[1][1] > rgb[0][1] ? 1 : -1;
	d_rgb[2] = rgb[1][2] > rgb[0][2] ? 1 : -1;
	len[0] = abs(rgb[1][0] - rgb[0][0]);
	len[1] = abs(rgb[1][1] - rgb[0][1]);
	len[2] = abs(rgb[1][2] - rgb[0][2]);
	int_color = (float)(abs(cursor - vertex_0[0])) /
				(float)(abs(vertex_0[0] - vertex_1[0]));
	color = (lround(rgb[0][0] + len[0] * int_color * d_rgb[0])) +
			(lround(rgb[0][1] + len[1] * int_color * d_rgb[1]) << 8) +
			(lround(rgb[0][2] + len[2] * int_color * d_rgb[2]) << 16);
	return (color);
}

int		set_yrgb(int *vertex_0, int *vertex_1, int cursor)
{
	unsigned char	*rgb[2];
	char			d_rgb[3];
	unsigned char	len[3];
	float			int_color;
	int				color;

	rgb[0] = (unsigned char *)&vertex_0[2];
	rgb[1] = (unsigned char *)&vertex_1[2];
	d_rgb[0] = rgb[1][0] > rgb[0][0] ? 1 : -1;
	d_rgb[1] = rgb[1][1] > rgb[0][1] ? 1 : -1;
	d_rgb[2] = rgb[1][2] > rgb[0][2] ? 1 : -1;
	len[0] = abs(rgb[1][0] - rgb[0][0]);
	len[1] = abs(rgb[1][1] - rgb[0][1]);
	len[2] = abs(rgb[1][2] - rgb[0][2]);
	int_color = (float)(abs(cursor - vertex_0[1])) /
				(float)(abs(vertex_0[1] - vertex_1[1]));
	color = (lround(rgb[0][0] + len[0] * int_color * d_rgb[0])) +
			(lround(rgb[0][1] + len[1] * int_color * d_rgb[1]) << 8) +
			(lround(rgb[0][2] + len[2] * int_color * d_rgb[2]) << 16);
	return (color);
}
