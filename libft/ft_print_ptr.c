/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 20:49:44 by ysakahar          #+#    #+#             */
/*   Updated: 2023/01/29 05:02:29 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_ptr_len(uintptr_t n)
{
	int	len;

	len = 0;
	while (n)
	{
		n /= 16;
		len++;
	}
	return (len);
}

void	ft_print_ptr_helper(uintptr_t n)
{
	if (n >= 16)
	{
		ft_print_ptr_helper(n / 16);
		ft_print_ptr_helper(n % 16);
	}
	else
	{
		if (n >= 10)
			ft_putchar_fd((n - 10 + 'a'), 1);
		else
			ft_putchar_fd((n + '0'), 1);
	}
}

int	ft_print_ptr(uintptr_t ptr)
{
	int	print_len;

	print_len = 0;
	print_len += ft_print_str("0x");
	if (!ptr)
		print_len += write(1, "0", 1);
	else
	{
		ft_print_ptr_helper(ptr);
		print_len += ft_ptr_len(ptr);
	}
	return (print_len);
}
