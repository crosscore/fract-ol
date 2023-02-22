/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 06:00:46 by ysakahar          #+#    #+#             */
/*   Updated: 2023/01/25 06:00:46 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

int		ft_printf(const char *format, ...);
int		ft_formats(va_list *args, const char format);
int		ft_print_char(int c);
int		ft_print_num(int n);
size_t	get_digits(int n);
char	*ft_itoa(int n);
int		ft_print_str(char *str);
int		ft_print_unsigned(unsigned int n);
int		ft_unum_len(unsigned int n);
int		ft_print_ptr(uintptr_t ptr);
void	ft_print_ptr_helper(uintptr_t n);
int		ft_ptr_len(uintptr_t n);
int		ft_print_hex(int n, const char format);
int		ft_print_hex_helper(unsigned int un, const char format);
int		ft_hex_len(int n);

#endif