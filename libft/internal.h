/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 23:18:06 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/15 14:17:09 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_H
# define INTERNAL_H

# include <stdarg.h>
# include <string.h>
# include <unistd.h>

void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putuint_fd(unsigned int n, int fd);
void	ft_putnbr_base(unsigned long nbr, char *base);
size_t	ft_strlen(const char *s);
int		print_number(va_list ap);
int		print_unsigned_number(va_list ap);
int		print_any_based_number(va_list ap, char *base, int base_count);
int		print_pointer(va_list ap, char *base);
int		print_string(va_list ap);
int		print_char(va_list ap);
int		any_base_numlen(long n, int base_count);
int		any_base_unsigned_numlen(unsigned long n, int base_count);

#endif