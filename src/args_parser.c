/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:18:55 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/26 15:34:30 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* skip_space_and_sign:
スペース、「+」および「-」記号文字をスキップし、
「-」記号が検出された場合は、signを-1に設定します。
Juliaのfloat値を表す文字列を解析するために使用されます。*/
static int	skip_space_and_sign(char *str, int *sign)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

/* ft_atof:
文字列をfloat(10進数)に変換します。
プログラムの引数として与えられたJuliaの開始値を解析するために使用されます。
変換されたdoubleか、-42(エラー時)を返します。
(Juliaは2.0から-2.0の間の値のみを受け入れます) */
double	ft_atof(char *str)
{
	double	float_n;
	double	div;
	int		i;
	int		sign;

	div = 0.1;
	sign = 1;
	float_n = 0;
	i = skip_space_and_sign(str, &sign);
	while (str[i] && ft_isdigit(str[i]) && str[i] != '.')
	{
		float_n = (float_n * 10.0) + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		float_n = float_n + ((str[i] - '0') * div);
		div *= 0.1;
		i++;
	}
	if (str[i] && !ft_isdigit(str[i]))
		return (-42);
	return (float_n * sign);
}

static int	skip_space_and_sign_and_0x(char *color)
{
	int	i;

	i = 0;
	while (ft_isspace(color[i]))
		i++;
	if (color[i] == '+')
		i++;
	if (color[i] == '0' && (color[i + 1]
			&& (color[i + 1] == 'x' || color[i + 1] == 'X')))
		i = i + 2;
	return (i);
}

static int	hexstring_to_color(t_fractol *f, char *color)
{
	int	i;
	int	x;
	int	n;

	n = 0;
	i = 0;
	i = skip_space_and_sign_and_0x(color);
	x = 0;
	while (color[i] && ft_ishexdigit(color[i]))
	{
		if (ft_isdigit(color[i]))
			n = (n * 16) + (color[i] - '0');
		else
			n = (n * 16) + (ft_toupper(color[i]) - 'A' + 10);
		i++;
		x++;
	}
	if (x == 6 && !color[i])
		return (n);
	else
		display_help(f);
	return (-1);
}

/* get_color:
プログラムの起動時に引数として指定された色のオプションを取得します。
色が指定されていない場合(argc == 2)は、デフォルト色をf->colorに設定します。
0x9966FF, 0x6680FF*/
void	get_color(t_fractol *f, int argc, char **argv)
{
	if (f->fractal_type == JULIA && argc == 5)
		f->base_color = hexstring_to_color(f, argv[4]);
	else if (f->fractal_type != JULIA && argc == 3)
		f->base_color = hexstring_to_color(f, argv[2]);
	if (argc == 2 || (f->fractal_type == JULIA && argc == 4))
		f->base_color = 0x6680FF;
}
