/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:18:49 by ysakahar          #+#    #+#             */
/*   Updated: 2023/02/22 14:05:22 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/* type_cmp:
指定されたフラクタルタイプの引数を解析し、名前 (「mandelbrot」)、
関連する文字 (「M」)、および関連する数字 (「1」) をチェックします。
引数がこれらの要件のいずれかに一致する場合はtrue、そうでない場合はfalseを返します。*/
static int	type_cmp(char *argv, char *str, char c, char n)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		argv[i] = ft_tolower(argv[i]);
		i++;
	}
	if (!ft_strncmp(argv, str, ft_strlen(str) + 1))
		return (1);
	else if (argv[1] == '\0' && (argv[0] == c || argv[0] == n))
		return (1);
	return (0);
}

/* get_set:
プログラム引数で指定されたセットを取得します。
有効なセットが指定されていない場合は、help_msgが表示され、プログラムが終了します。*/
static void	get_set(t_fractol *f, char **argv)
{
	if (type_cmp(argv[1], "mandelbrot", 'm', '1'))
		f->set_type = MANDELBROT;
	else if (type_cmp(argv[1], "julia", 'j', '2'))
		f->set_type = JULIA;
	else if (type_cmp(argv[1], "burning ship", 'b', '3'))
		f->set_type = BURNING_SHIP;
	else if (type_cmp(argv[1], "tricorn", 't', '4'))
		f->set_type = TRICORN;
	else if (type_cmp(argv[1], "mandelbox", 'x', '5'))
		f->set_type = MANDELBOX;
	else
		help_msg(f);
}

/* get_julia_starting_values:
Juliaセットのプログラム起動時に開始値が提供されたかどうかを確認します。
そうでない場合は、デフォルトのJulia値が割り当てられます。
値が提供された場合は、それらを解析し、値が有効でない場合はエラーメッセージを返します。*/
static void	get_julia_starting_values(t_fractol *f, int argc, char **argv)
{
	if (f->set_type != JULIA || argc == 2)
	{
		f->kr = -0.766667;
		f->ki = -0.090000;
		return ;
	}
	if (argc == 3)
		help_msg(f);
	if (!ft_strchr(argv[2], '.'))
		help_msg(f);
	if (!ft_strchr(argv[3], '.'))
		help_msg(f);
	f->kr = ft_atof(argv[2]);
	f->ki = ft_atof(argv[3]);
	if (f->kr > 2.0 || f->kr < -2.0)
		help_msg(f);
	if (f->ki >= 2.0 || f->ki <= -2.0)
		help_msg(f);
}

/* handle_args:
プログラムの起動時に渡された引数から、
セット、ジュリアの開始値、色を取得します。*/
static void	handle_args(t_fractol *f, int argc, char **argv)
{
	get_set(f, argv);
	if (f->set_type != JULIA && argc > 3)
		help_msg(f);
	else if (f->set_type == JULIA && argc > 5)
		help_msg(f);
	get_julia_starting_values(f, argc, argv);
	get_color(f, argc, argv);
}

/* main:
fractolデータ構造を初期化し、プログラムコントロールを出力し、
新しいウィンドウを開き、フックを登録してユーザーの操作を検出します。
ユーザーがプロセスを終了するまで無限にループします。*/
int	main(int argc, char **argv)
{
	t_fractol	*f;

	f = malloc(sizeof(t_fractol));
	if (!f)
		return (1);
	initialize_fractol(f);
	if (argc < 2)
	{
		help_msg(f);
		free(f);
		return (0);
	}
	handle_args(f, argc, argv);
	init(f);
	render(f);
	print_controls();
	mlx_hook(f->win, EVENT_CLOSE_BTN, 0, end_fractol, f);
	mlx_key_hook(f->win, key_event, f);
	mlx_mouse_hook(f->win, mouse_event, f);
	mlx_loop(f->mlx);
	free(f);
	return (0);
}

/*
__attribute__((destructor)) static void	destructor(void)
{
	system("leaks -q fractol");
}
*/
