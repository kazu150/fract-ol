/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 18:53:17 by kaisogai          #+#    #+#             */
/*   Updated: 2025/08/07 18:09:06 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

static void	update_coordinate_offset(int x, int y, t_vars *v, int is_zoom_out)
{
	if (is_zoom_out)
	{
		v->x_offset = v->x_offset / ZOOM_LEVEL + (x - WIDTH / 2);
		v->y_offset = v->y_offset / ZOOM_LEVEL + (y - HEIGHT / 2);
	}
	else
	{
		v->x_offset = v->x_offset * ZOOM_LEVEL + (x - WIDTH / 2);
		v->y_offset = v->y_offset * ZOOM_LEVEL + (y - HEIGHT / 2);
	}
}

void	clean_exit(t_vars *v)
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
	free(v);
	exit(0);
}

int	handle_key(int keycode, t_vars *v)
{
	if (keycode == KEY_ESC)
		clean_exit(v);
	else
	{
		if (keycode == KEY_UP_ARROW)
			v->y_offset = v->y_offset - KEY_MOVE_RANGE;
		if (keycode == KEY_DOWN_ARROW)
			v->y_offset = v->y_offset + KEY_MOVE_RANGE;
		if (keycode == KEY_LEFT_ARROW)
			v->x_offset = v->x_offset - KEY_MOVE_RANGE;
		if (keycode == KEY_RIGHT_ARROW)
			v->x_offset = v->x_offset + KEY_MOVE_RANGE;
		if (keycode == KEY_1)
			v->color_range_pattern = COLOR_RANGE_L;
		if (keycode == KEY_2)
			v->color_range_pattern = COLOR_RANGE_M;
		if (keycode == KEY_3)
			v->color_range_pattern = COLOR_RANGE_S;
		draw(v);
	}
	return (0);
}

int	handle_close(t_vars *v)
{
	clean_exit(v);
	return (0);
}

int	event_handler(int button, int x, int y, void *param)
{
	t_vars	*v;

	v = (t_vars *)param;
	if (button == 4)
	{
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
