/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:57:24 by kaisogai          #+#    #+#             */
/*   Updated: 2025/08/01 17:16:12 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

t_complex	complex_mul(t_complex a, t_complex b)
{
	return ((t_complex){a.real * b.real - a.imag * b.imag, a.real * b.imag
		+ a.imag * b.real});
}

t_complex	complex_add(t_complex a, t_complex b)
{
	return ((t_complex){a.real + b.real, a.imag + b.imag});
}

int	color(int i)
{
	if (i < 3)
		return (0xffc1e0);
	if (i < 7)
		return (0xffc1ff);
	if (i < 10)
		return (0xe0c1ff);
	if (i < 20)
		return (0xc1c1ff);
	if (i < 30)
		return (0xc1e0ff);
	if (i < 50)
		return (0xc1ffff);
	if (i < 100)
		return (0xc1ffe0);
	if (i < 150)
		return (0xc1ffc1);
	if (i < 200)
		return (0xe0ffc1);
	if (i < 250)
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
				c.real = 0.27334;
				c.imag = 0.00742;
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
			v->x_offset = v->x_offset / ZOOM_LEVEL + (x - WIDTH / 2);
			v->y_offset = v->y_offset / ZOOM_LEVEL + (y - HEIGHT / 2);
		}
		else
		{
			v->x_offset = 0;
			v->y_offset = 0;
		}
	}
	else
	{
		v->x_offset = v->x_offset * ZOOM_LEVEL + (x - WIDTH / 2);
		v->y_offset = v->y_offset * ZOOM_LEVEL + (y - HEIGHT / 2);
	}
}

int	event_handler(int button, int x, int y, void *param)
{
	t_vars	*v;

	v = (t_vars *)param;
	if (button == 4)
	{
		if (v->zoom > 1)
			v->zoom /= ZOOM_LEVEL;
		update_coordinate_offset(x, y, v, 1);
		draw(v);
	}
	else if (button == 5)
	{
		v->zoom *= ZOOM_LEVEL;
		update_coordinate_offset(x, y, v, 0);
		draw(v);
	}
	return (0);
}

static void	clean_exit(t_vars *v)
{
	if (v->img.img_ptr)
		mlx_destroy_image(v->mlx, v->img.img_ptr);
	if (v->win)
		mlx_destroy_window(v->mlx, v->win);
	if (v->mlx)
	{
		mlx_destroy_display(v->mlx);
		free(v->mlx);
	}
	exit(0);
}

static int	handle_key(int keycode, t_vars *v)
{
	if (keycode == KEY_ESC)
		clean_exit(v);
	else
	{
		if (keycode == KEY_UP_ARROW)
			v->y_offset = v->y_offset - 30;
		if (keycode == KEY_DOWN_ARROW)
			v->y_offset = v->y_offset + 30;
		if (keycode == KEY_LEFT_ARROW)
			v->x_offset = v->x_offset - 30;
		if (keycode == KEY_RIGHT_ARROW)
			v->x_offset = v->x_offset + 30;
		draw(v);
	}
	return (0);
}

static int	handle_close(t_vars *v)
{
	clean_exit(v);
	return (0);
}

int	is_num(char *target)
{
	char	dot_already_exists;
	int		i;

	dot_already_exists = 0;
	i = 0;
	if (target[0] == '-' || target[0] == '+')
		i++;
	while (target[i])
	{
		if (!ft_isdigit(target[i]) && target[i] != '.')
			return (0);
		if (target[i] == '.')
		{
			if (dot_already_exists)
				return (0);
			if (i == 0 || target[i + 1] == 0)
				return (0);
			dot_already_exists = 1;
		}
		i++;
	}
	return (1);
}
static int	invalid_param(int argc, char **argv)
{
	if (argc < 2)
		return (0);
	if (ft_strncmp(argv[1], "m", 2) == 0 && argc == 2)
		return (0);
	if (ft_strncmp(argv[1], "j", 2) == 0 && argc == 4 && is_num(argv[2])
		&& is_num(argv[3]))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_vars	*v;

	if (invalid_param(argc, argv))
	{
		ft_printf("valid param list\nm: mandelbrot\nj real_num imaginary_num: julia\n");
		exit(0);
	}
	v = malloc(sizeof(t_vars));
	v->zoom = 1;
	v->mlx = mlx_init();
	v->win = mlx_new_window(v->mlx, WIDTH, HEIGHT, "fractol");
	v->x_offset = 0;
	v->y_offset = 0;
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
