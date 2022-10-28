/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_mini_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnochiza <fnochiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:40:46 by fnochiza          #+#    #+#             */
/*   Updated: 2022/09/05 18:40:54 by fnochiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_com_new1(t_cmd	*cmd, char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	cmd->arg = malloc(sizeof(char *) * i + 1);
	if (!cmd->arg)
		return ;
	cmd->arg[i] = NULL;
	i = -1;
	while (arr[++i])
		cmd->arg[i] = ft_substr(arr[i], 0, ft_strlen(arr[i]));
}

int	make_arg(char ***arg, char **arr, int i)
{
	int		n;
	int		j;

	j = 0;
	n = ft_n_words(arr, i);
	if (n == 0)
	{
		*arg = NULL;
		return (0);
	}
	*arg = malloc(sizeof(char *) * (n + 1));
	while (j < n)
	{
		(*arg)[j++] = ft_substr(arr[i], 0, ft_strlen(arr[i]));
		i++;
	}
	(*arg)[j] = NULL;
	return (n);
}

t_cmd	*com_new1(char *name, char **arr, int redir, char *file)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->name = ft_substr(name, 0, ft_strlen(name));
	ft_free(name);
	if (arr)
	{
		fill_com_new1(cmd, arr);
		free_array(arr);
	}
	else
		cmd->arg = NULL;
	cmd->redir = redir;
	cmd->file = ft_substr(file, 0, ft_strlen(file));
	cmd->next = NULL;
	return (cmd);
}

int	ft_new_cmd(int i, char **arr, t_cmd **new)
{
	char	*name;
	char	**arg;

	name = ft_substr(arr[i], 0, ft_strlen(arr[i]));
	i++;
	i = i + make_arg(&arg, arr, i);
	if (arr[i] && delimetr(arr[i]) > 1)
	{
		*new = com_new1(name, arg, delimetr(arr[i]), arr[i + 1]);
		i = i + 2;
	}
	else if (arr[i] && delimetr(arr[i]) == 1)
	{
		i++;
		*new = com_new1(name, arg, 1, 0);
	}
	else
		*new = com_new1(name, arg, 0, 0);
	return (i);
}

void	ft_struct(char **arr, t_cmd **cmd)
{
	t_cmd	*new;
	t_cmd	*tmp;
	int		i;

	new = NULL;
	*cmd = init_cmd();
	tmp = *cmd;
	i = 0;
	while (arr[i])
	{
		make_struct(arr, &i, &new);
		cmd_add_back(cmd, new);
	}
	*cmd = (*cmd)->next;
	ft_one_name(cmd);
	free(tmp);
}
