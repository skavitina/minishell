/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_mini_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnochiza <fnochiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:25:16 by fnochiza          #+#    #+#             */
/*   Updated: 2022/09/05 18:50:35 by fnochiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_to_string_from_array(char **array, int i)
{
	char	*tmp;

	while (array[i])
	{
		if (!ft_strcmp(array[i], "$?"))
		{
			tmp = ft_itoa(g_exit_status);
			ft_putstr_fd(tmp, 1);
			ft_free(tmp);
		}
		else
			ft_putstr_fd(array[i], 1);
		if (array[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
}

int	ft_echo(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		if (!cmd->arg)
		{
			ft_putchar_fd('\n', 1);
		}
		else if (!ft_strcmp(cmd->arg[i], "-n"))
		{
			while (!ft_strcmp(cmd->arg[i], "-n"))
				i++;
			print_to_string_from_array(cmd->arg, i);
		}
		else
		{
			print_to_string_from_array(cmd->arg, i);
			ft_putchar_fd('\n', 1);
		}
		cmd = cmd->next;
	}
	return (0);
}
