/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 13:37:54 by kaisogai          #+#    #+#             */
/*   Updated: 2025/08/04 12:58:01 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

double	os_calc(int position, int size, double offset, double scale)
{
	return ((position - size / 2.0 + offset) * scale);
}

static int	sign(char s)
{
	if (s == '-')
		return (-1);
	else
		return (1);
}

double	atod(char *str)
{
	double	decimal_part;
	int		i;
	int		dot_index;
	double	devide_value;

	i = 0;
	dot_index = 0;
	decimal_part = 0;
	devide_value = 10.0;
	while (str[i])
	{
		if (str[i] == '.')
		{
			str[i] = 0;
			dot_index = i;
		}
		else if (dot_index)
		{
			decimal_part += (str[i] - '0') / devide_value;
			devide_value *= 10;
		}
		i++;
	}
	return (ft_atoi(str) + (decimal_part * sign(str[0])));
}
