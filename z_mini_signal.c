/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_mini_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnochiza <fnochiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:38:51 by fnochiza          #+#    #+#             */
/*   Updated: 2022/09/06 20:56:00 by fnochiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals2(void)
{
	extern int	rl_catch_signals;

	rl_catch_signals = 1;
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, ctrl_c);
}

void	handle_signals(void)
{
	extern int	rl_catch_signals;

	rl_catch_signals = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c);
}

void	ctrl_c(int sig)
{
	printf("\n");
	(void) sig;
	if (g_exit_status != 0)
	{
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}
