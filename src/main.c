/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:57:24 by kaisogai          #+#    #+#             */
/*   Updated: 2025/08/01 18:57:52 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

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
	t_complex	z;
	t_complex	c;
	int			is_inside;
	t_complex	min;
	t_complex	max;
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
	c.real = min.real;
	scale = 4.0 / (WIDTH * v->zoom);
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (v->set.set_type == MANDELBROT_SET)
			{
				c.real = (x - WIDTH / 2.0 + v->x_offset) * scale;
				c.imag = (y - HEIGHT / 2.0 + v->y_offset) * scale;
				z = (t_complex){0, 0};
			}
			else
			{
				c.real = v->set.complex.real;
				c.imag = v->set.complex.imag;
				z = (t_complex){(x - WIDTH / 2.0 + v->x_offset) * scale, (y
						- HEIGHT / 2.0 + v->y_offset) * scale};
			}
			i = 0;
			is_inside = 1;
			while (i < CALC_MAX)
			{
				z = complex_add(complex_mul(z, z), c);
				if (sqrt(z.real * z.real + z.imag * z.imag) > 2)
				{
					is_inside = 0;
					break ;
				}
				i++;
			}
			if (!is_inside)
			{
				put_to_image(&v->img, x, y, color(v->color_range_pattern, i));
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

int	main(int argc, char **argv)
{
	t_vars	*v;

	if (invalid_param(argc, argv))
	{
		ft_printf("valid param list\n");
		ft_printf("m: mandelbrot set\n");
		ft_printf("j real_num imaginary_num: julia set\n");
		exit(0);
	}
	v = malloc(sizeof(t_vars));
	v->zoom = 1;
	v->mlx = mlx_init();
	v->win = mlx_new_window(v->mlx, WIDTH, HEIGHT, "fractol");
	v->x_offset = 0;
	v->y_offset = 0;
	v->color_range_pattern = COLOR_RANGE_L;
	if (ft_strncmp(argv[1], "m", 2) == 0)
		v->set.set_type = MANDELBROT_SET;
	if (ft_strncmp(argv[1], "j", 2) == 0)
	{
		v->set.set_type = JULIA_SET;
		v->set.complex.real = ft_atoi(argv[2]);
		v->set.complex.imag = ft_atoi(argv[3]);
	}
	mlx_mouse_hook(v->win, event_handler, v);
	mlx_hook(v->win, EVENT_KEY_PRESS, MASK_KEY_PRESS, handle_key, v);
	mlx_hook(v->win, EVENT_DESTROY, 0, handle_close, v);
	draw(v);
	mlx_loop(v->mlx);
}
