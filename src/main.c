/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:57:24 by kaisogai          #+#    #+#             */
/*   Updated: 2025/07/26 17:40:17 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

s_complex	complex_mul(s_complex a, s_complex b)
{
	return ((s_complex){a.real * b.real - a.imag * b.imag, a.real * b.imag
		+ a.imag * b.real});
}

s_complex	complex_add(s_complex a, s_complex b)
{
	return ((s_complex){a.real + b.real, a.imag + b.imag});
}

int	color(int i)
{
	if (i < 5)
		return (0x333333);
	if (i < 10)
		return (0x666666);
	return (0xbbbbbb);
}

void	put_to_image(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = img->data + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw(t_vars *v)
{
	int			i;
	s_complex	z;
	s_complex	res;
	int			is_inside;
	double		real_max;
	double		imag_max;
	int			x;
	int			y;

	z.real = ((WIDTH / 2 - v->x_offset) / WIDTH - 2) / v->zoom;
	real_max = z.real + 4 / v->zoom;
	z.imag = ((HEIGHT / 2 - v->y_offset) / HEIGHT - 2) / v->zoom;
	imag_max = z.imag + 4 / v->zoom;
	printf("zoom:%f\n", v->zoom);
	printf("offset[%f,%f]\n", v->x_offset, v->y_offset);
	printf("real[%f,%f,%f]\n", z.real, real_max, real_max - z.real);
	printf("imag[%f,%f,%f]\n", z.imag, imag_max, imag_max - z.imag);
	fflush(stdout);
	v->img.img_ptr = mlx_new_image(v->mlx, WIDTH, HEIGHT);
	v->img.data = mlx_get_data_addr(v->img.img_ptr, &v->img.bpp,
			&v->img.size_line, &v->img.endian);
	while (z.real < real_max)
	{
		z.real += 0.01 / v->zoom;
		z.imag = -2;
		while (z.imag < imag_max)
		{
			z.imag += 0.01 / v->zoom;
			i = 0;
			res = (s_complex){0, 0};
			is_inside = 1;
			while (i < 100)
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
			{
				x = z.real * v->zoom * 100 + v->x_offset;
				y = z.imag * v->zoom * 100 + v->y_offset;
				put_to_image(&v->img, x, y, color(i));
			}
		}
	}
	mlx_put_image_to_window(v->mlx, v->win, v->img.img_ptr, 0, 0);
}

void	update_coordinate_offset(int x, int y, t_vars *v)
{
	if (v->zoom > 1)
	{
		v->x_offset = v->x_offset - (x - WIDTH / 2) / v->zoom;
		v->y_offset = v->y_offset - (y - HEIGHT / 2) / v->zoom;
	}
	else
	{
		v->x_offset = WIDTH / 2;
		v->y_offset = HEIGHT / 2;
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
		update_coordinate_offset(x, y, v);
		draw(v);
	}
	else if (button == 5)
	{
		mlx_clear_window(v->mlx, v->win);
		if (v->zoom < 100)
			v->zoom *= 1.2;
		update_coordinate_offset(x, y, v);
		draw(v);
	}
	return (0);
}

int	main(void)
{
	t_vars	*v;

	v = malloc(sizeof(t_vars));
	v->zoom = 1;
	v->mlx = mlx_init();
	v->win = mlx_new_window(v->mlx, WIDTH, HEIGHT, "fractol");
	v->x_offset = WIDTH / 2;
	v->y_offset = HEIGHT / 2;
	mlx_mouse_hook(v->win, event_handler, v);
	draw(v);
	mlx_loop(v->mlx);
}
