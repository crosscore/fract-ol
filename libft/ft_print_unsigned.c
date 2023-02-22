/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 08:36:39 by ysakahar          #+#    #+#             */
/*   Updated: 2023/01/28 03:10:50 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_unum_len(unsigned int n)
{
	int	len;

	len = 0;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

int	ft_print_unsigned(unsigned int n)
{
	int		print_len;
	char	*str;
	int		len;

	print_len = 0;
	if (n == 0)
		print_len += write(1, "0", 1);
	else
	{
		len = ft_unum_len(n);
		str = (char *)malloc(sizeof(char) * (len + 1));
		if (!str)
			return (0);
		str[len] = '\0';
		while (n)
		{
			str[len - 1] = n % 10 + '0';
			n /= 10;
			len--;
		}
		print_len += ft_print_str(str);
		free(str);
	}
	return (print_len);
}
