/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 18:39:04 by kaisogai          #+#    #+#             */
/*   Updated: 2025/08/01 18:49:01 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	color(int pattern, int i)
{
	const int	color_range_l[] = {COLOR_RANGE_L_VALUES};
	const int	color_range_m[] = {COLOR_RANGE_M_VALUES};
	const int	color_range_s[] = {COLOR_RANGE_S_VALUES};
	const int	*color_ranges[] = {color_range_l, color_range_m, color_range_s};

	if (i < color_ranges[pattern][0])
		return (0xffc1e0);
	if (i < color_ranges[pattern][1])
		return (0xffc1ff);
	if (i < color_ranges[pattern][2])
		return (0xe0c1ff);
	if (i < color_ranges[pattern][3])
		return (0xc1c1ff);
	if (i < color_ranges[pattern][4])
		return (0xc1e0ff);
	if (i < color_ranges[pattern][5])
		return (0xc1ffff);
	if (i < color_ranges[pattern][6])
		return (0xc1ffe0);
	if (i < color_ranges[pattern][7])
		return (0xc1ffc1);
	if (i < color_ranges[pattern][8])
		return (0xe0ffc1);
	return (0xffffc1);
}
