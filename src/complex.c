/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 18:38:06 by kaisogai          #+#    #+#             */
/*   Updated: 2025/08/01 18:41:15 by kaisogai         ###   ########.fr       */
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
