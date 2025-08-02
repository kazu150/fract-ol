/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:57:24 by kaisogai          #+#    #+#             */
/*   Updated: 2025/08/02 16:33:18 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	main(int argc, char **argv)
{
	t_vars	*v;

	validate_params(argc, argv);
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
		v->set.complex.real = atod(argv[2]);
		v->set.complex.imag = atod(argv[3]);
		printf("%f,%f", atod(argv[2]), atod(argv[3]));
		fflush(stdout);
	}
	mlx_mouse_hook(v->win, event_handler, v);
	mlx_hook(v->win, EVENT_KEY_PRESS, MASK_KEY_PRESS, handle_key, v);
	mlx_hook(v->win, EVENT_DESTROY, 0, handle_close, v);
	draw(v);
	mlx_loop(v->mlx);
}
