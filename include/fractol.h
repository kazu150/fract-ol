/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:58:10 by kaisogai          #+#    #+#             */
/*   Updated: 2025/08/01 18:49:15 by kaisogai         ###   ########.fr       */
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
# define EVENT_KEY_PRESS 2
# define MASK_KEY_PRESS (1L << 0)
# define EVENT_DESTROY 17
# define MANDELBROT_SET 1
# define JULIA_SET 2
# define COLOR_RANGE_L 0
# define COLOR_RANGE_M 1
# define COLOR_RANGE_S 2
# define COLOR_RANGE_S_VALUES 15, 25, 35, 60, 110, 160, 210, 260, 280
# define COLOR_RANGE_M_VALUES 10, 15, 25, 35, 60, 100, 140, 180, 210
# define COLOR_RANGE_L_VALUES 2, 4, 6, 8, 10, 20, 30, 40, 50

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
}				t_vars;

t_complex		complex_mul(t_complex a, t_complex b);
t_complex		complex_add(t_complex a, t_complex b);
int				invalid_param(int argc, char **argv);
int				color(int pattern, int i);

#endif