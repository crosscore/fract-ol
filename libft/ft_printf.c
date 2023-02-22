/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 06:01:01 by ysakahar          #+#    #+#             */
/*   Updated: 2023/01/25 06:01:01 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_formats(va_list *args, const char format)
{
	int	print_len;

	print_len = 0;
	if (format == 'c')
		print_len += ft_print_char(va_arg(*args, int));
	else if (format == 'd' || format == 'i')
		print_len += ft_print_num(va_arg(*args, int));
	else if (format == 'p')
		print_len += ft_print_ptr(va_arg(*args, uintptr_t));
	else if (format == 's')
		print_len += ft_print_str(va_arg(*args, char *));
	else if (format == 'u')
		print_len += ft_print_unsigned(va_arg(*args, unsigned int));
	else if (format == 'x' || format == 'X')
		print_len += ft_print_hex(va_arg(*args, int), format);
	else if (format == '%')
		print_len += ft_print_char('%');
	return (print_len);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		print_len;
	size_t	i;

	va_start(args, str);
	print_len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			print_len += ft_formats(&args, str[i]);
		}
		else
		{
			print_len += ft_print_char(str[i]);
		}
		i++;
	}
	va_end(args);
	return (print_len);
}
