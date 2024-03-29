/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:24:13 by jthuy             #+#    #+#             */
/*   Updated: 2020/04/16 15:03:39 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <stddef.h>
# include <fcntl.h>
# include <stdarg.h>
# include <wchar.h>
# include "../libft/libft.h"
# include "colors.h"
# define WIDTH 1920
# define HEIGHT 1080
# define SPEED_R 6
# define SPEED_M 4
# define SPEED_S1 0.5
# define SPEED_S2 0.1
# define ROT_X -60
# define ROT_Y -30
# define ROT_Z 0
# define PARSER_MEMALLOCATE_ERR 12
# define PARSER_WRONGMAP_ERR 13
# define PARSER_OPENFILE_ERR 14
# define PARSER_WRONGCONTENT_ERR 15
# define DIVIDE_SYMBOL ' '
# define AMOUNT_OF_PARAMETERS_PER_DOT 3
# define UIBUTTON_W 200
# define UIBUTTON_H 50
# define UIBOX_W 350

typedef struct		s_sys
{
	void			*mlx;
	void			*win;
	void			*img;
	int				img_s[3];
	int				field;
	int				*output;
	int				*back_buf;
	int				*z_buf;
	char			render;
	char			control;
	int				mouse_pos[2];
}					t_sys;

typedef struct		s_model
{
	int				**vertex;
	int				width;
	int				height;
	int				area;
	char			*diagonal;
	short			pos[2];
	short			rot[3];
	float			scale;
	float			**o_vertex;
	float			first_scale;
	short			first_pos[2];
	char			color_f;
	char			*modelname;
	int				z_max;
	int				z_min;
	int				z_result;
}					t_model;

typedef struct		s_coords
{
	int				counter[2];
	int				index[4];
	float			tmp[3];
	float			f_quad[4][3];
	int				d_quad[4][3];
	int				d_tris[3][3];
	float			f_tris[3];
	int				d_line[2][3];
	float			f_line[3];
}					t_coords;

typedef struct		s_setting
{
	t_sys			sys;
	t_model			model;
	t_coords		coords;
}					t_setting;

typedef struct		s_backset
{
	unsigned char	color_rgb[2][3];
	char			d[3];
	unsigned char	len[3];
}					t_back;

typedef struct		s_printbuf
{
	int				x;
	int				y;
	int				number_of_triangles;
	char			*vertexes;
	char			*trianges;
	char			*modelname;
	char			*max_x;
	char			*max_y;
	char			*max_z;
	char			*pivot_x;
	char			*pivot_y;
	char			*rot_x;
	char			*rot_y;
	char			*rot_z;
	char			*u_s;
	char			*rend_mode;
	char			*color_en;
	char			*projection;
}					t_pb;

/*
** fdf.c
*/
int					set_model(char *filename, t_model *model, t_coords *coords);
void				set_system(t_sys *sys, t_model *model);
void				clean_frame(t_sys *sys, t_model *model);
int					close_fdf(void *param);
void				error_handler(int parse_status);

/*
** parser.c
*/
int					parse(char *filename, t_model *model);
int					read_file(int fd, char **splitted_line, t_model *model);
void				model_init(t_model *model);
int					parse_color(char *word, t_model *model, int default_color);
int					allocate_mem(char *filename, t_model *model);
int					fill_matrix(t_model *model, char **line_of_z,
						int i_starts_from, int y);
void				calc_z_max(t_model *model, int val);
int					check_point(char *str);
char				*parse_name(char *str);
int					ft_wordscounter(char const *str, char c);

/*
** menu.c
*/
void				print_left_manual_text(t_sys *system, int *st, int c);
void				print_right_manual_text(t_setting *s, int *st, t_pb *pb);
void				print_left_text(t_setting *setting, int c);
void				print_right_text(t_setting *setting, int c);
void				print_two_small_buttons_text(t_setting *setting, int c);
void				print_left_manual_text_ad(t_sys *system, int *st, int c);
void				print_right_manual_text_ad(t_setting *s, int c, t_pb *pb);
void				print_right_manual_text_a(t_setting *s, int c, t_pb *pb);
void				print_right_manual_text_2(t_setting *s, t_pb *pb);
void				print_right_manual_text_1(t_setting *s, t_pb *pb);

/*
** utils.c
*/
int					ft_isspace(int c);
int					ft_isnumber(char *str, int base);
int					ft_atoi_base(const char *str, int base);

/*
** set_model.c
*/
void				set_diagonal(t_model *model);
float				len_diag(int *vertex_0, int *vertex_1);
void				pre_transform(t_model *model);
void				set_overall(t_model *model);

/*
** set_scale.c
*/
void				set_scalepos(t_model *model, t_coords *coords);
void				set_minmaxvert(t_model *model, float *vert_min,
						float *vert_max);
void				fill_overtex(t_model *model, t_coords *coords);
void				setup_quad(t_model *model, t_coords *coords, int *k);
void				shift_quadvert(t_coords *coords);

/*
** set_system.c
*/
void				set_buffers(t_sys *sys);
void				set_backbuf(int *back_buf);
t_back				*set_backset(void);
int					backcolor(float cursor, t_back *backset);

/*
** def_transform.c
*/
void				transform_model(t_sys *sys, t_model *model,
						t_coords *coords);
char				draw_zeroscale(t_sys *sys, t_model *model);
void				transform_quad(t_sys *sys, t_model *model,
						t_coords *coords, int k);
char				vertz_zbuf(t_sys *sys, t_coords *coords);

/*
** transform.c
*/
void				rotate_quad(t_model *model, t_coords *coords, int k);
void				persp_distortion(t_model *model, t_coords *coords, int k);
void				scale_quad(t_model *model, t_coords *coords, int k);
void				move_quad(t_model *model, t_coords *coords, int k);
void				round_quad(t_model *model, t_coords *coords, int k);

/*
** render_mode.c
*/
void				draw_model(t_sys *sys, t_model *model, t_coords *coords);
void				draw_quad(t_sys *sys, t_model *model, t_coords *coords);
void				fill_quad(t_sys *sys, t_model *model, t_coords *coords);
void				fill_qmesh(t_sys *sys, t_model *model, t_coords *coords);
void				re_render(t_setting *setting);

/*
** r_vertex.c
*/
void				draw_qvertex(t_sys *sys, t_model *model, t_coords *coords);
void				vert_zbuf(t_sys *sys, t_coords *coords, int i);
void				vert_updownlines(t_sys *sys, t_coords *coords,
						int *i, int *j);
void				vert_nozbuf(t_sys *sys, t_coords *coords, int i);
char				vert_onscreen(int *i, t_coords *coords);

/*
** r_wireframe_noz.c
*/
void				quad_nozbuf(t_sys *sys, t_model *model, t_coords *coords);
void				defline_nozbuf(t_coords *coords, int v1, int v2);
void				line_nozbuf(t_sys *sys, t_coords *coords);
void				xmore_nozbuf(t_sys *sys, t_coords *coords,
						char *d, int *len);
void				ymore_nozbuf(t_sys *sys, t_coords *coords,
						char *d, int *len);

/*
** r_wireframe_z.c
*/
void				quad_zbuf(t_sys *sys, t_model *model, t_coords *coords);
void				defline_zbuf(t_coords *coords, int v1, int v2);
void				line_zbuf(t_sys *sys, t_coords *coords);
void				xmore_zbuf(t_sys *sys, t_coords *coords, char *d, int *len);
void				ymore_zbuf(t_sys *sys, t_coords *coords, char *d, int *len);

/*
** ortholines.c
*/
void				linex_nozbuf(t_sys *sys, int *vertex_0, int *vertex_1);
void				liney_nozbuf(t_sys *sys, int *vertex_0, int *vertex_1);
void				linex_zbuf(t_sys *sys, int *vertex_0,
						int *vertex_1, float *tris_z);
void				fill_pixel(t_sys *sys, int *vertex_0,
						int *vertex_1, int cursor);
void				liney_zbuf(t_sys *sys, int *vertex_0,
						int *vertex_1, float *tris_z);

/*
** r_silhouette.c
*/
void				fquad_nozbuf(t_sys *sys, t_model *model, t_coords *coords);
void				deftris_nozbuf(t_coords *coords, int v1, int v2, int v3);
void				ftris_nozbuf(t_sys *sys, t_coords *coords);
void				sorty_nozbuf(t_coords *coords);
void				setlinex_nozbuf(t_coords *coords, int *height, int i);

/*
** except_quad.c
*/
char				lastvert_qcolor(t_sys *sys, t_model *model,
						t_coords *coords);
void				lastl_zbuf(t_sys *sys, t_model *model, t_coords *coords);
void				lastvert_qnocol(t_sys *sys, t_model *model,
						t_coords *coords);
void				lastl_nozbuf(t_sys *sys, t_model *model, t_coords *coords);
char				check_zbuf(t_sys *sys, t_coords *coords,
						int *cursor, int dir);

/*
** r_mesh1.c
*/
void				fquad_zbuf(t_sys *sys, t_model *model, t_coords *coords);
void				deftris_zbuf(t_coords *coords, int v1, int v2, int v3);
void				fqmesh_nocolor(t_sys *sys, t_model *model,
						t_coords *coords);
void				set_shadetris(t_coords *coords, char v0, char v1, char v2);
void				set_light(t_coords *coords, int v0, int v1, int v2);

/*
** r_mesh2.c
*/
void				fqmesh_color(t_sys *sys, t_model *model, t_coords *coords);
void				shade_vtris(t_coords *coords);
int					shade_color(int color, float light);
int					set_xrgb(int *vertex_0, int *vertex_1, int cursor);
int					set_yrgb(int *vertex_0, int *vertex_1, int cursor);

/*
** filltris_zbuf.c
*/
void				ftris_zbuf(t_sys *sys, t_coords *coords);
void				sorty_zbuf(t_coords *coords);
void				sorty_zbuf2(t_coords *coords, int i);
void				setlinex_zbuf(t_sys *sys, t_coords *coords,
						int *height, int i);
void				lastvlx_zbuf(t_sys *sys, t_coords *coords);

/*
** except_qmesh.c
*/
char				lastvert_qmesh(t_sys *sys, t_model *model,
						t_coords *coords);
char				firsthor_qmcolor(t_sys *sys, t_model *model,
						t_coords *coords);
char				lasthor_qmcolor(t_sys *sys, t_model *model,
						t_coords *coords);
char				firsthor_qmnocol(t_sys *sys, t_model *model,
						t_coords *coords);
char				lasthor_qmnocol(t_sys *sys, t_model *model,
						t_coords *coords);

/*
** render_ui.c
*/
void				ui_boxcontrols(t_setting *setting);
void				ui_boxinfo(t_setting *setting);
void				get_rgba(int *color);
void				ui_buttons(t_setting *setting);

/*
** controls_main.c
*/
int					key_press(int keycode, void *param);
int					key_release(int keycode, void *param);
int					mouse_press(int button, int x,
						int y, void *param);
int					mouse_release(int button, int x,
						int y, void *param);
int					mouse_move(int x, int y, void *param);

/*
** controls_keybrd.c
*/
char				render_mode1(t_setting *setting, int keycode);
char				render_mode2(t_setting *setting, int keycode);
char				render_option(t_setting *setting, int keycode);
char				switch_uipanels(t_setting *setting, int keycode);
char				rescale(t_setting *setting, int keycode);

/*
** controls_mouse.c
*/
char				mouse_scale(t_setting *setting,
						int button, int x, int y);
char				mouse_uipanels(t_setting *setting, int x, int y);
char				mouse_mrotation(t_setting *setting, int x,
						int y, char inv_y);
char				mouse_mmove(t_setting *setting, int x, int y);
char				mouse_mscale(t_setting *setting, int x, int y);

/*
** controls_debug.c
*/
void				debug_input(t_setting *setting, int keycode);
void				debug_rotatex(t_setting *setting, int keycode);
void				debug_rotatey(t_setting *setting, int keycode);
void				debug_move(t_setting *setting, int keycode);
char				z_rotation(t_setting *setting, int keycode);

#endif
