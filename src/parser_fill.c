/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 21:56:55 by admin             #+#    #+#             */
/*   Updated: 2020/04/16 15:18:42 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fill_vertex(t_model *model, int *a, char **line_of_z)
{
	model->vertex[a[0]][0] = (a[0] - a[1]);
	model->vertex[a[0]][1] = a[2];
	model->vertex[a[0]][2] = ft_atoi(line_of_z[a[0] - a[1]]);
	model->vertex[a[0]][3] = parse_color(line_of_z[a[0] - a[1]],
				model, COLOR_DEF);
}

int		fill_matrix(t_model *model, char **line_of_z, int i_starts_from, int y)
{
	int a[4];

	a[0] = i_starts_from;
	a[1] = i_starts_from;
	a[2] = y;
	if (ft_arraylen(line_of_z) != model->width)
		return (0);
	while (a[0] < (i_starts_from + model->width))
	{
		if (!(model->vertex[a[0]] = (int *)malloc(sizeof(int) *
					AMOUNT_OF_PARAMETERS_PER_DOT)))
		{
			write(1, "malloc error\n", 13);
			return (0);
		}
		else if (check_point(line_of_z[a[0] - i_starts_from]))
		{
			fill_vertex(model, a, line_of_z);
			calc_z_max(model, model->vertex[a[0]][2]);
			a[0]++;
		}
		else
			return (0);
	}
	return (1);
}

void	error_handler(int parse_status)
{
	if (parse_status == PARSER_WRONGMAP_ERR)
		write(1, "Wrong map\n", 10);
	else if (parse_status == PARSER_WRONGCONTENT_ERR)
		write(1, "Wrong content\n", 14);
	else if (parse_status == PARSER_MEMALLOCATE_ERR)
		write(1, "Memory allocation failed\n", 25);
	else if (parse_status == PARSER_OPENFILE_ERR)
		write(1, "Error opening file\n", 19);
}
