/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 23:29:36 by ysakahar          #+#    #+#             */
/*   Updated: 2023/01/31 10:53:21 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex_helper(unsigned int un, const char format)
{
	char	buf[9];
	int		i;
	int		start;
	int		print_len;

	i = 7;
	while (i >= 0)
	{
		if ((un & 0xF) < 10)
			buf[i] = '0' + (un & 0xF);
		else if (format == 'x')
			buf[i] = 'a' + (un & 0xF) - 10;
		else
			buf[i] = 'A' + (un & 0xF) - 10;
		un >>= 4;
		i--;
	}
	buf[8] = '\0';
	start = 0;
	while (buf[start] == '0' && start < 8)
		start++;
	print_len = 8 - start;
	write(1, buf + start, print_len);
	return (print_len);
}

int	ft_print_hex(int n, const char format)
{
	unsigned int	un;
	int				print_len;

	if (n < 0)
		un = (unsigned int) n;
	else
		un = n;
	if (un == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	print_len = ft_print_hex_helper(un, format);
	return (print_len);
}
