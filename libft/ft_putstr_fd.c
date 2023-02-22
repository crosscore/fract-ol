/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 01:13:47 by ysakahar          #+#    #+#             */
/*   Updated: 2023/01/13 01:13:47 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;
	size_t	j;
	ssize_t	ret;
	size_t	bytes_to_write;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i])
		i++;
	j = 0;
	while (j < i)
	{
		bytes_to_write = i - j;
		if (bytes_to_write > INT_MAX)
			bytes_to_write = INT_MAX;
		ret = write(fd, s + j, bytes_to_write);
		if (ret == -1)
			break ;
		j += ret;
	}
}
