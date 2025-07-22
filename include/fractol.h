/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:58:10 by kaisogai          #+#    #+#             */
/*   Updated: 2025/07/22 17:45:12 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/libft.h"
#include "../include/fractol.h"
#include "../mlx/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <math.h>
#include <stdio.h>

typedef struct t_complex
{
	double	real;
	double	imag;
}			s_complex;

#endif