/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multibrot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:00:27 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/26 10:40:41 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	multibrot(double cr, double ci)
{
	int		i;
	double	re;
	double	im;
	double	re_prev;
	double	exp;

	i = 0;
	re = 0;
	im = 0;
	re_prev = 0;
	exp = MULTI;
	while (i < MAX_ITERATIONS)
	{
		re_prev = re;
		re = pow(re, exp) - pow(im, exp) + cr;
		im = 2 * re_prev * im + ci;
		if (re * re + im * im > 4.0)
			break ;
		i++;
	}
	return (i);
}
