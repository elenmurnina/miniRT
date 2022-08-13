/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nposidon <nposidon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 10:55:35 by nposidon          #+#    #+#             */
/*   Updated: 2022/08/09 10:59:11 by nposidon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <stdlib.h>
# include <unistd.h>

# include "mlx/mlx.h"
# include "libft/libft/libft.h"

# include <float.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# define HEIGHT 1500
# define WIDTH 1000
# define TRUE 1
# define FALSE 0
# define DEEP_REFLECTION 200
# define PRESIGION 1
# define CHECBOARD 41

enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	TRIANGLE,
};

typedef struct vec {
	double	x;
	double	y;
	double	z;
}				t_vector;

typedef struct t_color {
	double	r;
	double	g;
	double	b;

}				t_color;

typedef struct s_texture
{
	void		*ptr;
	char		*img;
	int			width;
	int			height;
	int			bpp;
	int			size_line;
	int			endian;
}				t_texture;

typedef struct t_object
{
	t_vector	coord_xyz;
	t_vector	vec_3d_norm;
	double		radius;
	double		height;
	int			type;
	t_vector	triangle_vertices[3];
	t_color		color;
	int			specular;
	int			checker_board;
	char		*file_text_name;
	char		*file_bump_name;
	t_texture	*texture;
	t_texture	*texture_bump;
}				t_object;

typedef struct t_light {
	t_vector	vec;
	double		power;
	t_color		color;
}				t_light;

typedef struct list {
	struct t_object	*a;
	struct list		*next;
}				t_list;

typedef struct list_light
{
	struct t_light		*l;
	struct list_light	*next;
}				t_list_light;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct sssa {
	t_data	*im;
	void	*mlx;
	void	*win;
	double	x;
	double	y;
	double	scale;
	int		color_key;
	int		repeats;
	char	fractall;
	int		flag;
	double	x0;
	double	y0;
}	t_mystr;

typedef struct miniRT
{
	t_object		*moved_obj;
	t_mystr			*a;
	t_vector		cam;
	t_vector		cam_norm_vec;
	t_vector		cam_x;
	t_vector		cam_y;
	t_light			fon;
	t_light			diffuse;
	int				fov_cam;
	int				_a;
	int				_c;
	t_list			*start;
	t_list_light	*start_light;
	int				sr_file_ts;
}				t_global;

typedef struct ht {
	double		dist;
	t_vector	hit;
	t_color		color;
	t_vector	norm;
}	t_point;

typedef struct triple {
	t_vector	x;
	t_vector	y;
	t_vector	xy;
	t_vector	loook;
	t_color		diffuse;
	t_color		specular;
	t_color		ref;
	double		exp;
	double		fi;
	double		pi;
}	t_triple;

t_color		create_color( double r, double b, double g);
int			ft_loop(t_global *global);
int			rbg(t_color a);
int			render_next_frame(t_mystr *myst, t_global *global);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			intersept_sphere(t_object sph, t_vector loook, t_vector cam,
				t_point *point);
double		vec_product_v2(t_vector a, t_vector b);
double		vect_mod(t_vector a);
t_vector	vec_product_v3(t_vector a, t_vector b);
t_vector	vec_plas(t_vector a, t_vector b);
t_vector	vec_minus(t_vector a, t_vector b);
t_vector	vec_norm(t_vector a);
t_vector	vec_create(double x, double y, double z);
t_color		intersept_object(t_global *global, t_vector cam, \
								t_vector loook, int rr);
t_vector	vec_mult(t_vector a, double f);
t_color		color_mult(t_color a, t_color b);
t_vector	vec_reflect(t_vector a, t_vector b);
t_color		color_norm(t_color a);
t_color		color_add(t_color a, t_color b);
double		ft_max(double a, double b);
t_color		color_multd(t_color a, double f);
t_object	*intersept_objet0(t_list *i, t_vector loook, t_vector cam,
				t_point *point);
int			sign(double a);

//global_init
void		add_to_list(t_list **start, void *A);
void		add_to_list_light(t_list_light **start, void *A);
t_object	*create_object(t_vector coord, t_color b, int type);
t_light		*create_light(t_vector A, t_color b, double power);
void		global_init(t_global *global, t_mystr *a);
void		minirt_error(char *error);

//parsing
void		parsing_read_scene(char *scene_file, t_global *global);
void		parsing_element(char *s, t_global *global);
t_color		parsing_color(char *s);
t_vector	parsing_coord(char *s);
t_vector	parsing_3d_norm_orient_vec(char *s);
int			is_valid_color(char *color);
int			is_valid_double(char *d);
int			parsing_specular_reflection(char **s);
int			parsing_checker_board(char **s);
int			check_tex(char *name_file_texture);
t_object	*get_plane_object(char **s);
t_object	*get_sphere_object(char **s);
t_object	*get_cylinder_object(char **s);
void		get_ligth_a(char **s, t_global *global, t_light **light);
void		get_light_l(char **s, t_light **light);

//triangles
void		parsing_ts(char **s, t_global *global);
void		parse_element_ts(char *s, t_global *global, \
				t_vector *verts, int *vert_cnt);
t_object	*create_triangle(t_vector *verts, int *face, int specular);

//textures
char		*return_name_file_tex(char **s);
char		*return_name_file_bump(char **s);
void		create_texture(t_global *rt, t_texture **texture, char *file_name);
t_color		get_color(t_texture *texture, double fi, double pi);
void		apply_textures(t_object obj, t_vector hit, t_color *color);
void		apply_bmp(t_object *obj, t_vector *norm, t_vector hit);

//free
void		free_global(t_global *global);
t_global	*manage_global(t_global *global);
int			ft_exit(t_global *global);
t_vector	circle(t_vector sph, double r, t_vector cam, t_vector loook);
int			ft_loop(t_global *global);
t_color		create_color(double r, double b, double g);
t_vector	rotat_x(t_vector a, double fi);
t_vector	rotat_y(t_vector a, double fi);
t_vector	rotat_z(t_vector a, double fi);
int			key_hook(int key, t_global *global);
void		phong(t_global *global, t_point point, t_triple *trip);
double		dist(t_vector a1, t_vector point1, t_vector a2, t_vector point2);
t_color		final_color(t_triple *trip, t_color color, int a);
int			intersept_plane(t_object sph, t_vector lok, t_vector cam,
				t_point *point);
int			intersept_cylinder(t_object sph, t_vector lok, t_vector cam,
				t_point *point);
int			intersept_trian(t_object sph, t_vector loook, t_vector cam,
				t_point *point);
void		checkerboard(t_object obj, t_vector hit, t_color *color);
#endif