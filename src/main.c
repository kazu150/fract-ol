/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:57:24 by kaisogai          #+#    #+#             */
/*   Updated: 2025/06/29 19:59:16 by kaisogai         ###   ########.fr       */
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

int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 300, 300, "Hello World");
	mlx_hook(mlx_win, KeyPress, KeyPressMask, event_handler, mlx);
	mlx_string_put(mlx, mlx_win, 50, 100, 0xFFFFFF, "Zoom: XX");
	mlx_loop(mlx);
}
