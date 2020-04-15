/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:56:08 by jthuy             #+#    #+#             */
/*   Updated: 2020/04/15 21:57:21 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*parse_name(char *str)
{
	int i;
	int size;

	i = ft_strlen(str);
	size = ft_strlen(str);
	if (str)
	{
		while (str[i] != '/' && i != 0)
		{
			i--;
		}
		i++;
		if (ft_strstr(str, ".fdf"))
			size -= 4;
	}
	return (ft_strsub(str, i, size - i));
}

int		parse_color(char *word, t_model *model, int default_color)
{
	char	**splitted_word;
	int		output;

	output = default_color;
	splitted_word = 0;
	splitted_word = ft_strsplit(word, ',');
	if (splitted_word[1])
	{
		output = ft_atoi_base(splitted_word[1], 16);
		model->color_f = 1;
	}
	ft_arrayfree(splitted_word);
	return (output);
}

int		read_file(int fd, char **splitted_line, t_model *model)
{
	char	*next_line;
	int		cnt;
	int		y_cnt;

	cnt = 0;
	y_cnt = 0;
	next_line = 0;
	while (get_next_line(fd, &next_line))
	{
		splitted_line = ft_strsplit(next_line, DIVIDE_SYMBOL);
		if (!fill_matrix(model, splitted_line, cnt, y_cnt))
			return (PARSER_WRONGCONTENT_ERR);
		free(next_line);
		if (splitted_line)
			ft_arrayfree(splitted_line);
		cnt += model->width;
		y_cnt++;
	}
	if (next_line)
		free(next_line);
	return (0);
}

int		parse(char *filename, t_model *model)
{
	int		fd;
	int		read_status;
	char	**splitted_line;

	fd = 0;
	splitted_line = 0;
	model_init(model);
	if (!allocate_mem(filename, model))
		return (PARSER_OPENFILE_ERR);
	fd = open(filename, O_RDONLY, 0);
	if (fd < 0)
		return (PARSER_OPENFILE_ERR);
	read_status = read_file(fd, splitted_line, model);
	close(fd);
	return (read_status);
}
