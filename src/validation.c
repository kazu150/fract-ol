/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 18:40:12 by kaisogai          #+#    #+#             */
/*   Updated: 2025/08/01 18:41:37 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

static int	is_num(char *target)
{
	char	dot_already_exists;
	int		i;

	dot_already_exists = 0;
	i = 0;
	if (target[0] == '-' || target[0] == '+')
		i++;
	while (target[i])
	{
		if (!ft_isdigit(target[i]) && target[i] != '.')
			return (0);
		if (target[i] == '.')
		{
			if (dot_already_exists)
				return (0);
			if (i == 0 || target[i + 1] == 0)
				return (0);
			dot_already_exists = 1;
		}
		i++;
	}
	return (1);
}

int	invalid_param(int argc, char **argv)
{
	if (argc < 2)
		return (1);
	if (ft_strncmp(argv[1], "m", 2) == 0 && argc == 2)
		return (0);
	if (ft_strncmp(argv[1], "j", 2) == 0 && argc == 4 && is_num(argv[2])
		&& is_num(argv[3]))
		return (0);
	return (1);
}
