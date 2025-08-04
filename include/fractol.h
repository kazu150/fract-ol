/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:58:10 by kaisogai          #+#    #+#             */
/*   Updated: 2025/08/04 16:38:36 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../include/fractol.h"
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>

# define WIDTH 600
# define HEIGHT 600
# define ZOOM_LEVEL 1.2
# define CALC_MAX 300
# define KEY_LEFT_ARROW 65361
# define KEY_UP_ARROW 65362
# define KEY_RIGHT_ARROW 65363
# define KEY_DOWN_ARROW 65364
# define KEY_ESC 65307
# define KEY_1 49
# define KEY_2 50
# define KEY_3 51
# define KEY_MOVE_RANGE 30
# define EVENT_KEY_PRESS 2
# define MASK_KEY_PRESS 1
# define EVENT_DESTROY 17
# define MANDELBROT_SET 1
# define JULIA_SET 2
# define COLOR_RANGE_L 0
# define COLOR_RANGE_M 1
# define COLOR_RANGE_S 2

typedef struct s_img
{
	void		*img_ptr;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
}				t_img;

typedef struct s_complex
{
	double		real;
	double		imag;
}				t_complex;

typedef struct s_set
{
	int			set_type;
	t_complex	complex;
}				t_set;

typedef struct s_vars
{
	t_set		set;
	int			color_range_pattern;
	void		*mlx;
	void		*win;
	double		zoom;
	double		x_offset;
	double		y_offset;
	t_img		img;
	double		scale;
}				t_vars;

typedef struct s_coordinate
{
	int			x;
	int			y;
}				t_coordinate;

t_complex		complex_mul(t_complex a, t_complex b);
t_complex		complex_add(t_complex a, t_complex b);
void			validate_params(int argc, char **argv);
int				color(int pattern, int i);
int				handle_key(int keycode, t_vars *v);
int				handle_close(t_vars *v);
int				event_handler(int button, int x, int y, void *param);
void			draw(t_vars *v);
double			os_calc(int position, int size, double offset, double scale);
double			atod(char *str);

#endif