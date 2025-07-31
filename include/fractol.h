/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:58:10 by kaisogai          #+#    #+#             */
/*   Updated: 2025/07/31 19:18:04 by kaisogai         ###   ########.fr       */
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
# define KEY_ESC 65307
# define EVENT_KEY_PRESS 2
# define MASK_KEY_PRESS (1L << 0)
# define EVENT_DESTROY 17
typedef struct s_img
{
	void	*img_ptr;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
}			t_img;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	double	zoom;
	double	x_offset;
	double	y_offset;
	t_img	img;
}			t_vars;

typedef struct t_complex
{
	double	real;
	double	imag;
}			s_complex;

#endif