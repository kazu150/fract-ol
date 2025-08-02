/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 13:37:54 by kaisogai          #+#    #+#             */
/*   Updated: 2025/08/02 16:44:50 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

double	os_calc(int position, int size, double offset, double scale)
{
	return ((position - size / 2.0 + offset) * scale);
}

double	atod(char *str)
{
	double	res;
	int		i;
	int		dot_index;
	char	*int_part;
	double	devide_value;

	int_part = ft_strdup(str);
	i = 0;
	dot_index = 0;
	devide_value = 10.0;
	res = 0;
	while (str[i])
	{
		if (str[i] == '.')
		{
			int_part[i] = 0;
			res = ft_atoi(int_part);
			dot_index = i;
		}
		else if (dot_index)
		{
			res += (str[i] - '0') / devide_value;
			devide_value *= 10;
		}
		i++;
	}
	if (!dot_index)
		res = ft_atoi(int_part);
	return (res);
}
