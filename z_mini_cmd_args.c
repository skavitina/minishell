/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_mini_cmd_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnochiza <fnochiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:22:54 by fnochiza          #+#    #+#             */
/*   Updated: 2022/09/05 18:23:17 by fnochiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_cmd(t_cmd *cmd, t_exec *exec)
{
	char	*tmp;
	char	*command;
	int		i;

	exec->cmd_full[0] = ft_strdup(cmd->name);
	i = 0;
	while (exec->path_cmd[i])
	{
		tmp = ft_strjoin(exec->path_cmd[i], "/");
		command = ft_strjoin(tmp, cmd->name);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

void	get_env(t_envp *env, t_exec *exec)
{
	t_envp	*envir;
	char	*tmp;
	int		i;

	envir = env;
	while (envir)
	{
		if (ft_strncmp("PATH", envir->key, 4) == 0)
			exec->path = envir->value;
		envir = envir->next;
	}
	exec->path_cmd = ft_split(exec->path, ':');
	i = envsize(env);
	exec->env = (char **)malloc (sizeof(char *) * (i + 2));
	i = 0;
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		exec->env[i] = ft_strjoin(tmp, env->value);
		env = env->next;
		free(tmp);
		i++;
	}
}

void	check_extra_args(t_cmd *coms, t_exec *exec, int i, int j)
{
	while (coms && coms->redir != 1)
	{
		if (coms->arg)
		{
			while (coms->arg[j])
			{
				exec->cmd_full[i] = ft_strdup(coms->arg[j]);
				i++;
				j++;
			}
		}
		j = 0;
		coms = coms->next;
	}
}

void	find_args(t_cmd *cmd, t_exec *exec)
{
	int		i;
	int		j;
	t_cmd	*tmp;

	tmp = cmd;
	i = 1;
	j = 0;
	if (tmp->redir == 1)
	{
		if (tmp->arg)
		{
			while (tmp->arg[j])
			{
				exec->cmd_full[i] = ft_strdup(tmp->arg[j]);
				i++;
				j++;
			}
		}
		if (!tmp->arg)
			exec->cmd_full[1] = (char *)malloc(sizeof(char *));
	}
	check_extra_args(tmp, exec, i, j);
}

void	check_cmd(t_cmd *cmd, t_exec *exec)
{
	char	*cmd_name;
	t_cmd	*command;

	command = cmd;
	if (ft_strncmp(command->name, "/", 1) == 0)
	{
		exec->cmd_exec = command->name;
		cmd_name = ft_strrchr(command->name, '/');
		cmd_name++;
		exec->cmd_full[0] = ft_strdup(cmd_name);
	}
	else
	{
		exec->cmd_exec = make_cmd(command, exec);
		if (!exec->cmd_exec)
		{
			ft_putstr_fd("<3: ", 2);
			ft_putstr_fd(command->name, 2);
			ft_putendl_fd(": command not found", 2);
			g_exit_status = 127;
			free_pipe_struct(exec);
			exit(127);
		}
	}
}
