/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_mini_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnochiza <fnochiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:29:38 by fnochiza          #+#    #+#             */
/*   Updated: 2022/09/05 18:50:10 by fnochiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp_list(t_envp *envp_list)
{
	if (!envp_list)
		return ;
	while (envp_list)
	{
		if (envp_list->key)
			free(envp_list->key);
		if (envp_list->value)
			free(envp_list->value);
		envp_list = envp_list->next;
	}
	free(envp_list);
	envp_list = NULL;
}

void	free_com_list(t_cmd *cmd)
{
	t_cmd	*tmp;

	if (cmd)
	{
		while (cmd)
		{
			tmp = cmd->next;
			if (cmd->name)
				free(cmd->name);
			if (cmd->arg)
				free_array(cmd->arg);
			if (cmd->file)
				free(cmd->file);
			cmd = tmp;
		}
		if (cmd)
			free(cmd);
	}
}

void	ft_free_com_list(t_cmd **cmd)
{
	t_cmd	*tmp;

	if (*cmd)
	{
		while (*cmd)
		{
			tmp = (*cmd)->next;
			if ((*cmd)->name)
				free((*cmd)->name);
			if ((*cmd)->arg)
				free_array((*cmd)->arg);
			if ((*cmd)->file)
				free((*cmd)->file);
			if (*cmd)
				free(*cmd);
			(*cmd) = tmp;
		}
		if ((*cmd))
			free((*cmd));
	}
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		if (arr[i])
		{
			while (arr[i])
			{
				free(arr[i]);
				i++;
			}
		}
		free(arr);
	}
}

void	ft_free(char *str)
{
	if (str)
		free(str);
}
