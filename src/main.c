/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:57:24 by kaisogai          #+#    #+#             */
/*   Updated: 2025/07/22 16:51:40 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"
#include "../libft/libft.h"
#include "../mlx/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <math.h>
#include <stdio.h>

typedef struct t_complex
{
	double	real;
	double	imag;
}			s_complex;

int	event_handler(int key, void *mlx)
{
	(void)key;
	(void)mlx;
	printf("called\n");
	return (0);
}

s_complex	complex_mul(s_complex a, s_complex b)
{
	return ((s_complex){a.real * b.real - a.imag * b.imag, a.real * b.imag
		+ a.imag * b.real});
}

s_complex	complex_add(s_complex a, s_complex b)
{
	return ((s_complex){a.real + b.real, a.imag + b.imag});
}

void	draw(void *mlx, void *mlx_win)
{
	int			i;
	s_complex	z;
	s_complex	res;
	int			is_inside;

	z = (s_complex){-2, -2};
	while (z.real < 2)
	{
		z.real += 0.01;
		z.imag = -1;
		while (z.imag < 2)
		{
			z.imag += 0.01;
			i = 0;
			res = (s_complex){0, 0};
			is_inside = 1;
			while (i < 20)
			{
				res = complex_mul(res, res);
				res = complex_add(res, z);
				if (sqrt(res.real * res.real + res.imag * res.imag) > 2)
				{
					is_inside = 0;
					break ;
				}
				i++;
			}
			if (is_inside)
				mlx_pixel_put(mlx, mlx_win, z.real * 100 + 250, z.imag * 100
					+ 250, 0xFFFFFF);
		}
	}
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 500, 500, "fractol");
	mlx_hook(mlx_win, FocusIn, FocusChangeMask, event_handler, mlx);
	draw(mlx, mlx_win);
	mlx_loop(mlx);
}
