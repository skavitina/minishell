/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_mini_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnochiza <fnochiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:28:42 by fnochiza          #+#    #+#             */
/*   Updated: 2022/09/06 20:00:59 by fnochiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	arguments_handler(char **array, t_cmd *cmd, t_envp *envp_list)
{
	int	i;

	i = 0;
	if (array[0][i] == '+' || array[0][i] == '-')
		i++;
	while (array[0][++i])
	{
		if (array[0][i] < '0' || array[0][i] > '9')
		{
			ft_putendl_fd("ḾĪŇĪŠĤĚĹĹ ⟹  : exit: numeric argument required", 2);
			free_com_list(cmd);
			free_envp_list(envp_list);
			exit(255);
		}
	}
	if (array[1])
		ft_putendl_fd("exit \nḾĪŇĪŠĤĚĹĹ ⟹  : exit: too many arguments", 2);
	else
	{
		i = ft_atoi(array[0]);
		ft_putendl_fd("exit", 1);
		free_com_list(cmd);
		free_envp_list(envp_list);
		exit(i);
	}
}

void	ft_exit(t_cmd *cmd, t_envp *envp_list)
{
	if (!cmd->arg)
	{
		ft_putendl_fd("exit", 1);
		free_com_list(cmd);
		free_envp_list(envp_list);
		exit(0);
	}
	else
		arguments_handler(cmd->arg, cmd, envp_list);
}
