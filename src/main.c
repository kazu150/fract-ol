/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:57:24 by kaisogai          #+#    #+#             */
/*   Updated: 2025/06/29 21:12:07 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"
#include "../libft/libft.h"
#include "../mlx/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <stdio.h>

int	event_handler(int key, void *mlx)
{
	printf("called\n");
	return (0);
}

void	draw(void *mlx, void *mlx_win)
{
	int	i;

	i = 0;
	while (i < 100)
	{
		mlx_pixel_put(mlx, mlx_win, i + 50, i + 50, 0xFFFFFF);
		i++;
	}
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 300, 300, "Hello World");
	mlx_hook(mlx_win, KeyPress, KeyPressMask, event_handler, mlx);
	draw(mlx, mlx_win);
	mlx_loop(mlx);
}
