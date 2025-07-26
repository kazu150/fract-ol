/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:58:10 by kaisogai          #+#    #+#             */
/*   Updated: 2025/07/26 15:45:37 by kaisogai         ###   ########.fr       */
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

typedef struct s_img
{
	void *img_ptr; // mlx_new_image() の戻り値を格納
	char *data;    // 画像バッファ
	int bpp;       // bits per pixel
	int size_line; // 1行のバイト数
	int endian;    // エンディアン
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