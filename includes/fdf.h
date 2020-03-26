/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:24:13 by jthuy             #+#    #+#             */
/*   Updated: 2020/03/23 17:30:37 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>


# include <stddef.h>
# include <fcntl.h>
# include <stdarg.h>
# include <wchar.h>
# include "../libft/libft.h"
// # include "minilibx_macos/mlx.h"


#include <stdio.h>


#include "colors.h"

#define WIDTH 1280
#define HEIGHT 720
#define SPEED_R 6
#define SPEED_M 4
#define SPEED_S1 0.5
#define SPEED_S2 0.1
#define ROT_X -60
#define ROT_Y -30
#define ROT_Z 0

# define DIVIDE_SYMBOL ' '
# define AMOUNT_OF_PARAMETERS_PER_DOT 3


typedef struct	s_system
{
	void		*mlx;
	void		*win;
	void		*img;
	int			img_s[3];
	int			field;
	int			*output;
	int			*back_buf;
	int			*z_buf;
	// int			*light_buf;
	char		render;
	char		control;
	int			mouse_pos[2];
}				t_system;

typedef struct	s_model
{
	int			**vertex;
	int			width;
	int			height;
	int			area;
	char		*diagonal;
	short		pos[2];
	short		rot[3];
	float		scale;
	// char		overall;
	float		**o_vertex;
	float		first_scale;
	short		first_pos[2];
	// int			max_coord;
	char		color_f;
	char		*modelname;
}				t_model;

typedef struct	s_coords
{
	int			counter[2];
	int			index[4];
	float		tmp[3];
	float		f_quad[4][3];
	int			d_quad[4][3];
	float		lightpower;
	int			tris_xy[3][2];
	float		tris_z[3];
}				t_coords;

typedef struct	s_setting
{
	t_system	system;
	t_model		model;
	t_coords	coords;
}				t_setting;


typedef struct		s_backset
{
	unsigned char	color_rgb[2][3];
	char			d[3];
	unsigned char	len[3];
}					t_back;


/*
** fdf.c
*/
// void	draw_line(t_system *system, int *vertex_1, int *vertex_2, int color);
// void	fill_triangle(t_system *system, int *vertex_0, int *vertex_1, int *vertex_2);
// void	sort_triangle_y(int **triangle);
// int		light_color(int color, float lightpower);
void	set_model(char *filename, t_model *model, t_coords *coords);
void	set_diagonal(t_model *model);
float	len_diag(int *vertex_0, int *vertex_1);
void	set_overall(t_model *model);
void	pre_transform(t_model *model);
void	set_system(t_system *system);
void	set_backbuf(int *back_buf);
int		close_fdf(void *param);
void	clean_frame(t_system *system, t_model *model);

/*
** parser.c
*/
int		ft_wordscounter(char const *str, char c);
int		check_point(char *str);
int		fill_matrix(t_model *model, char **line_of_z, int i_starts_from, int y);
int		allocate_mem(char *filename, t_model *model);
int		parse_color(char *word, t_model *model, int default_color);
int		parse(char *filename, t_model *model);

/*
** utils.c
*/
int			ft_isspace(int c);
// static int	ft_isdigit_base(char c, int base);
// static int	ft_has_prefix(const char *str, int base);
int			ft_isnumber(char *str, int base);
int			ft_atoi_base(const char *str, int base);


// void	set_overall(t_model *model);
// void	set_maxcoord(t_model *model);

/*
** set_background.c
*/
void	set_buffers(t_system *system);
t_back	*set_backset();
int		backcolor(float cursor, t_back *backset);


/*
** set_scale.c
*/
void	set_scalepos(t_model *model, t_coords *coords);
void	set_minmaxvert(t_model *model, float *vert_min, float *vert_max);
void	fill_overtex(t_model *model, t_coords *coords);
void	setup_quad(t_model *model, t_coords *coords, int *k);
void	shift_quadvert(t_coords *coords);

/*
** transform.c
*/
void	transform_model(t_system *system, t_model *model, t_coords *coords);
void	rotate_quad(t_model *model, t_coords *coords, int k);
void	persp_distortion(t_model *model, t_coords *coords, int k);
void	scale_quad(t_model *model, t_coords *coords, int k);
void	move_quad(t_model *model, t_coords *coords, int k);
void	round_quad(t_model *model, t_coords *coords, int k);


/*
** controls_main.c
*/
int		key_press(int keycode, void *param);
int		mouse_press(int button, int x, int y, void *param);
int		mouse_release(int button, int x, int y, void *param);
int		mouse_move(int x, int y, void *param);
void	controls_test(t_setting *setting, int keycode);

/*
** drawing.c
*/
char	draw_zeroscale(t_system *system, t_model *model);
void	draw_model(t_system *system, t_model *model, t_coords *coords);

// UNCOMENT
void	draw_quad(t_system *system, t_model *model, t_coords *coords);
void	draw_line(t_system *system, int *vertex_0, int *vertex_1, char color_f);
void	draw_horizontal(t_system *system, int *vertex_0, int *vertex_1, char color_f);
int		set_colorhor(int *vertex_0, int *vertex_1, int cursor);


// void	fill_quad(t_system *system, t_coords *coords);
// void	fill_qmesh(t_system *system, t_model *model, t_coords *coords);
// void	draw_qvertex(t_system *system, t_coords *coords);


/*
** r_vertex.c
*/
void	draw_qvertex(t_system *system, t_model *model, t_coords *coords);
void	vert_zbuf(t_system *system, t_coords *coords);
void	vert_updownlines(t_system *system, t_coords *coords, int *i, int *j);
void	vert_nozbuf(t_system *system, t_coords *coords);
char	vert_onscreen(int *i, t_coords *coords);

// /*
// ** draw_line.c
// */
// void	draw_line(t_system *system, int *vertex_1, int *vertex_2, int color);
// void	x_more_y(t_system *system, int *vertex_0, int *vertex_1, int color);
// void	y_more_x(t_system *system, int *vertex_0, int *vertex_1, int color);
// int		set_diffuse(int *vertex_0, int *vertex_1, int *coord);



// /*
// ** controls.c
// */
// int		key_press(int keycode, void *param);
// int		mouse_press(int button, int x, int y, void *param);
// int		mouse_release(int button, int x, int y, void *param);
// int		mouse_move(int x, int y, void *param);
// void	clean_frame(t_system *system);


// /*
// ** def_data.c
// */
// // void	*get_mem(int size);
// void	set_params(t_model *model);
// void	set_model(t_model *model);
// void	shift_to_origin(t_model *model);
// void	set_coords(t_coords *coords);
// void	set_diagonal(t_model *model);
// float	len_diag(int *vertex_0, int *vertex_1);
// void	set_buffers(t_system *system);

// /*
// ** transform.c
// */
// void	transform_model(t_system *system, t_model *model, t_coords *coords);
// void	setup_quad(t_model *model, t_coords *coords, int *k);
// void	rotate_quad(t_model *model, t_coords *coords, int k);
// void	persp_distortion(t_model *model, t_coords *coords, int k);
// void	scale_quad(t_model *model, t_coords *coords, int k);
// void	move_quad(t_model *model, t_coords *coords, int k);
// void	round_quad(t_coords *coords, int k);
// float	set_lightpower(t_system *system, float *vertex_0, float *vertex_1, float *vertex_2);
// void	set_scale(t_model *model);

// /*
// ** drawing.c
// */
// void	draw_model(t_system *system, t_model *model, t_coords *coords);
// void	draw_quad(t_system *system, t_model *model, t_coords *coords);
// void	fill_quad(t_system *system, t_coords *coords);
// void	fill_qmesh(t_system *system, t_model *model, t_coords *coords);
// void	draw_qvertex(t_system *system, t_coords *coords);

// /*
// ** draw_line.c
// */
// void	draw_line(t_system *system, int *vertex_1, int *vertex_2, int color);
// void	x_more_y(t_system *system, int *vertex_0, int *vertex_1, int color);
// void	y_more_x(t_system *system, int *vertex_0, int *vertex_1, int color);
// int		set_diffuse(int *vertex_0, int *vertex_1, int *coord);

// /*
// ** fill_triangle.c
// */
// void	fill_triangle(t_system *system, t_coords *coords);
// void	sort_triangle_y(t_coords *coords);

// /*
// ** parser.c
// */
// int		ft_wordscounter(char const *str, char c);
// void	fill_matrix(t_model *model, char **line_of_z, int i_starts_from, int y);
// int		allocate_mem(char *filename, t_model *model);
// int		parse(char *filename, t_model *model);


#endif