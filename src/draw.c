/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:25:11 by kaisogai          #+#    #+#             */
/*   Updated: 2025/08/02 13:37:43 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

static void	put_image(t_img *img, t_coordinate co, int color)
{
	char	*dst;

	if (co.x < 0 || co.y < 0 || co.x >= WIDTH || co.y >= HEIGHT)
		return ;
	dst = img->data + (co.y * img->size_line + co.x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	initialize_vars(t_vars *v)
{
	v->img.img_ptr = mlx_new_image(v->mlx, WIDTH, HEIGHT);
	v->img.data = mlx_get_data_addr(v->img.img_ptr, &v->img.bpp,
			&v->img.size_line, &v->img.endian);
	v->scale = 4.0 / (WIDTH * v->zoom);
}

static void	calc(t_vars *v, t_coordinate co, t_complex z, t_complex c)
{
	int	i;

	i = 0;
	while (i < CALC_MAX)
	{
		z = complex_add(complex_mul(z, z), c);
		if (sqrt(z.real * z.real + z.imag * z.imag) > 2)
		{
			put_image(&v->img, co, color(v->color_range_pattern, i));
			return ;
		}
		i++;
	}
	return ;
}

void	draw_main(t_vars *v, t_coordinate co)
{
	t_complex	z;
	t_complex	c;

	if (v->set.set_type == MANDELBROT_SET)
	{
		c.real = os_calc(co.x, WIDTH, v->x_offset, v->scale);
		c.imag = os_calc(co.y, HEIGHT, v->y_offset, v->scale);
		z = (t_complex){0, 0};
	}
	else
	{
		c = (t_complex){v->set.complex.real, v->set.complex.imag};
		z.real = os_calc(co.x, WIDTH, v->x_offset, v->scale);
		z.imag = os_calc(co.y, HEIGHT, v->y_offset, v->scale);
	}
	calc(v, co, z, c);
}

void	draw(t_vars *v)
{
	t_coordinate	co;

	initialize_vars(v);
	co.x = 0;
	while (co.x < WIDTH)
	{
		co.y = 0;
		while (co.y < HEIGHT)
		{
			draw_main(v, co);
			co.y++;
		}
		co.x++;
	}
	mlx_put_image_to_window(v->mlx, v->win, v->img.img_ptr, 0, 0);
}
