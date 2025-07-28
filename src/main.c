/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:57:24 by kaisogai          #+#    #+#             */
/*   Updated: 2025/07/28 19:01:59 by kaisogai         ###   ########.fr       */
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
	if (i < 3)
		return (0xffc1e0);
	if (i < 5)
		return (0xffc1ff);
	if (i < 7)
		return (0xe0c1ff);
	if (i < 10)
		return (0xc1c1ff);
	if (i < 13)
		return (0xc1e0ff);
	if (i < 16)
		return (0xc1ffff);
	if (i < 20)
		return (0xc1ffe0);
	if (i < 27)
		return (0xc1ffc1);
	if (i < 40)
		return (0xe0ffc1);
	if (i < 50)
		return (0xffffc1);
	return (0xffe0c1);
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
	s_complex	c;
	int			is_inside;
	s_complex	min;
	s_complex	max;
	int			x;
	int			y;
	double		scale;

	x = 0;
	y = 0;
	min.real = ((WIDTH / 2 - v->x_offset) / WIDTH - 2) / v->zoom;
	min.imag = ((HEIGHT / 2 - v->y_offset) / HEIGHT - 2) / v->zoom;
	max.real = min.real + 4 / v->zoom;
	max.imag = min.imag + 4 / v->zoom;
	v->img.img_ptr = mlx_new_image(v->mlx, WIDTH, HEIGHT);
	v->img.data = mlx_get_data_addr(v->img.img_ptr, &v->img.bpp,
			&v->img.size_line, &v->img.endian);
	z.real = min.real;
	scale = 4.0 / (WIDTH * v->zoom);
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			z.real = (x - WIDTH / 2.0 + v->x_offset) * scale;
			z.imag = (y - HEIGHT / 2.0 + v->y_offset) * scale;
			i = 0;
			c = (s_complex){0, 0};
			is_inside = 1;
			while (i < 100)
			{
				c = complex_add(complex_mul(c, c), z);
				if (sqrt(c.real * c.real + c.imag * c.imag) > 2)
				{
					is_inside = 0;
					break ;
				}
				i++;
			}
			if (!is_inside)
			{
				put_to_image(&v->img, x, y, color(i));
			}
			y++;
		}
		x++;
	}
	printf("zoom:%f\n", v->zoom);
	printf("offset[%f,%f]\n", v->x_offset, v->y_offset);
	fflush(stdout);
	mlx_put_image_to_window(v->mlx, v->win, v->img.img_ptr, 0, 0);
}

void	update_coordinate_offset(int x, int y, t_vars *v, int is_zoom_out)
{
	if (is_zoom_out)
	{
		if (v->zoom > 1)
		{
			v->x_offset = v->x_offset / 1.2;
			v->y_offset = v->y_offset / 1.2;
		}
		else
		{
			v->x_offset = 0;
			v->y_offset = 0;
		}
	}
	else
	{
		v->x_offset = v->x_offset + (x - WIDTH / 2) * v->zoom / 2;
		v->y_offset = v->y_offset + (y - HEIGHT / 2) * v->zoom / 2;
	}
}

int	event_handler(int button, int x, int y, void *param)
{
	t_vars	*v;

	v = (t_vars *)param;
	if (button == 4)
	{
		if (v->zoom > 1)
			v->zoom /= 1.2;
		update_coordinate_offset(x, y, v, 1);
		draw(v);
	}
	else if (button == 5)
	{
		if (v->zoom < 100)
			v->zoom *= 1.2;
		update_coordinate_offset(x, y, v, 0);
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
	v->x_offset = 0;
	v->y_offset = 0;
	mlx_mouse_hook(v->win, event_handler, v);
	draw(v);
	mlx_loop(v->mlx);
}
