/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:57:24 by kaisogai          #+#    #+#             */
/*   Updated: 2025/07/25 19:18:21 by kaisogai         ###   ########.fr       */
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
	int		x_center;
	int		y_center;
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

int	calc_center(double zoom, int size, int position)
{
	int	center;

	if (zoom > 1)
		center = size / 2 - (position - size / 2) / 2 * zoom;
	else
		center = size / 2;
	return (center);
}

double	offset(double zoom, int size, int position)
{
	double	o;

	o = (double)calc_center(zoom, size, position) / (double)size;
	return (o);
}

int	color(int i)
{
	if (i < 5)
		return (0x333333);
	if (i < 10)
		return (0x666666);
	return (0xbbbbbb);
}
void	draw(t_vars *v)
{
	int			i;
	s_complex	z;
	s_complex	res;
	int			is_inside;

	z.real = (double)(v->x_center - v->width / 2) / v->width / v->zoom - 2
		/ v->zoom;
	z.imag = (double)(v->y_center - v->height / 2) / v->height / v->zoom - 2
		/ v->zoom;
	printf("centr[%d,%d]\n", v->x_center, v->y_center);
	printf("zahyo[%f,%f]\n", z.real, z.imag);
	fflush(stdout);
	while (z.real < 2 / v->zoom - (double)(v->x_center - v->width / 2) / 100
		* v->zoom)
	{
		z.real += 0.01 / v->zoom;
		z.imag = -2;
		while (z.imag < 2 / v->zoom - (double)(v->y_center - v->height / 2)
			/ 100 * v->zoom)
		{
			z.imag += 0.01 / v->zoom;
			i = 0;
			res = (s_complex){0, 0};
			is_inside = 1;
			while (i < 30)
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
			if (!is_inside)
				mlx_pixel_put(v->mlx, v->win, z.real * v->zoom * 100
					+ v->x_center, z.imag * v->zoom * 100 + v->y_center,
					color(i));
		}
	}
}

void	update_coordinate_center(int x, int y, t_vars *v)
{
	if (v->zoom > 1)
	{
		v->x_center = v->x_center - (x - v->width / 2);
		v->y_center = v->y_center - (y - v->height / 2);
	}
	else
	{
		v->x_center = v->width / 2;
		v->y_center = v->height / 2;
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
		update_coordinate_center(x, y, v);
		draw(v);
	}
	else if (button == 5)
	{
		mlx_clear_window(v->mlx, v->win);
		if (v->zoom < 100)
			v->zoom *= 1.2;
		update_coordinate_center(x, y, v);
		draw(v);
	}
	return (0);
}

int	main(void)
{
	t_vars	*v;

	v = malloc(sizeof(t_vars));
	v->width = 600;
	v->height = 600;
	v->zoom = 1;
	v->mlx = mlx_init();
	v->win = mlx_new_window(v->mlx, v->width, v->height, "fractol");
	v->x_center = v->width / 2;
	v->y_center = v->height / 2;
	mlx_mouse_hook(v->win, event_handler, v);
	draw(v);
	mlx_loop(v->mlx);
}
