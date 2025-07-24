/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:57:24 by kaisogai          #+#    #+#             */
/*   Updated: 2025/07/24 18:51:06 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	double	zoom;
}			t_vars;

s_complex	complex_mul(s_complex a, s_complex b)
{
	return ((s_complex){a.real * b.real - a.imag * b.imag, a.real * b.imag
		+ a.imag * b.real});
}

s_complex	complex_add(s_complex a, s_complex b)
{
	return ((s_complex){a.real + b.real, a.imag + b.imag});
}

void	draw(t_vars *v, double x, double y)
{
	int			i;
	s_complex	z;
	s_complex	res;
	int			is_inside;

	z = (s_complex){(-2 + (x - v->width) / v->width) / v->zoom, (-2 + (y
				- v->height) / v->zoom) / v->height};
	printf("[x: %f, x / v->width: %f, y: %f, y / v->height: %f]", x, x
		/ v->width, y, y / v->height);
	while (z.real < 2 / v->zoom)
	{
		z.real += 0.01 / v->zoom;
		z.imag = -1;
		while (z.imag < 2 / v->zoom)
		{
			z.imag += 0.01 / v->zoom;
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
				mlx_pixel_put(v->mlx, v->win, z.real * v->zoom * 100 + (x - 200)
					* v->zoom + v->width / 2, z.imag * v->zoom * 100 + (y - 200)
					* v->zoom + v->height / 2, 0xFFFFFF);
		}
	}
}

int	event_handler(int button, int x, int y, void *param)
{
	t_vars	*v;

	v = (t_vars *)param;
	if (button == 4)
	{
		mlx_clear_window(v->mlx, v->win);
		if (v->zoom > 1)
			v->zoom /= 1.2;
		draw(v, (double)x, (double)y);
	}
	else if (button == 5)
	{
		mlx_clear_window(v->mlx, v->win);
		if (v->zoom < 10)
			v->zoom *= 1.2;
		draw(v, (double)x, (double)y);
	}
	return (0);
}
int	main(void)
{
	t_vars	*v;

	v = malloc(sizeof(t_vars));
	v->width = 400;
	v->height = 400;
	v->zoom = 1;
	v->mlx = mlx_init();
	v->win = mlx_new_window(v->mlx, v->width, v->height, "fractol");
	mlx_mouse_hook(v->win, event_handler, v);
	draw(v, (double)(v->width / 2), (double)(v->height / 2));
	mlx_loop(v->mlx);
}
