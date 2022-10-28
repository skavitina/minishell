/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_mini_exec_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnochiza <fnochiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:27:23 by fnochiza          #+#    #+#             */
/*   Updated: 2022/09/05 18:27:32 by fnochiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lstsize(t_cmd *lst)
{
	int	i;

	i = 0;
	if (lst)
	{
		while (lst)
		{
			i++;
			lst = lst->next;
		}
	}
	return (i);
}

int	envsize(t_envp *lst)
{
	int	i;

	i = 0;
	if (lst)
	{
		while (lst)
		{
			i++;
			lst = lst->next;
		}
	}
	return (i);
}

int	count_array(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->arg[i])
		i++;
	return (i);
}

int	count_pipes(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		pipes;

	pipes = 0;
	tmp = cmd;
	while (tmp)
	{
		if (tmp->redir == 1)
			pipes++;
		tmp = tmp->next;
	}
	return (pipes);
}
