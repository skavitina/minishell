/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_mini_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnochiza <fnochiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:28:12 by fnochiza          #+#    #+#             */
/*   Updated: 2022/09/06 20:57:15 by fnochiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_full_com(t_cmd *cmd, t_exec *exec)
{
	t_cmd	*full_cmd;
	t_cmd	*cmd_name;
	int		cmd_num;

	cmd_num = 1;
	full_cmd = cmd;
	cmd_name = cmd;
	while (full_cmd && full_cmd->redir != 1 && cmd_num++)
		full_cmd = full_cmd->next;
	exec->cmd_full = (char **)malloc(sizeof(char *) * (cmd_num * 10));
	if (!exec->cmd_full)
		return ;
	if (cmd_name->redir == 0 || cmd_name->redir == 1)
		check_cmd(cmd_name, exec);
	while (cmd_name && cmd_name->redir != 1)
	{
		if (cmd_name->name)
		{
			check_cmd(cmd_name, exec);
			break ;
		}
		cmd_name = cmd_name->next;
	}
	find_args(cmd, exec);
}

void	execve_handler(t_cmd *cmd, t_exec *exec, t_envp *envp_list)
{
	int	exit_status;
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		get_env(envp_list, exec);
		make_full_com(cmd, exec);
		execve(exec->cmd_exec, exec->cmd_full, exec->env);
		ft_putstr_fd("ḾĪŇĪŠĤĚĹĹ ⟹  : ", 2);
		perror(exec->cmd_full[0]);
		g_exit_status = 127;
		free_pipe_struct(exec);
		exit(127);
	}
	wait(&exit_status);
	if (WIFSIGNALED(exit_status))
	{
		if (WTERMSIG(exit_status) != 13)
			g_exit_status = 128 + WTERMSIG(exit_status);
		if (WTERMSIG(exit_status) == SIGQUIT)
			ft_putendl_fd("Quit", 2);
	}
	else
		g_exit_status = WEXITSTATUS(exit_status);
}

void	executor(t_cmd *cmd, t_envp **envp_list, t_exec *exec)
{
	if (!ft_strcmp(cmd->name, "echo") || !ft_strcmp(cmd->name, "ECHO"))
		g_exit_status = ft_echo(cmd);
	else if (!ft_strcmp(cmd->name, "env") || !ft_strcmp(cmd->name, "ENV"))
		g_exit_status = ft_env(*envp_list);
	else if (!ft_strcmp(cmd->name, "pwd") || !ft_strcmp(cmd->name, "PWD"))
		g_exit_status = ft_pwd(*envp_list);
	else if (!ft_strcmp(cmd->name, "cd"))
		g_exit_status = ft_cd(cmd, *envp_list);
	else if (!ft_strcmp(cmd->name, "export"))
		g_exit_status = ft_export(cmd, envp_list);
	else if (!ft_strcmp(cmd->name, "unset"))
		g_exit_status = ft_unset(cmd, envp_list);
	else if (!ft_strcmp(cmd->name, "exit"))
		ft_exit(cmd, *envp_list);
	else
		execve_handler(cmd, exec, *envp_list);
}

void	execute(t_cmd *cmd, t_envp **env)
{
	t_exec	exec;

	exec.pipe_num = count_pipes(cmd);
	if (cmd->redir != 0)
		pipe_handler(cmd, env, &exec);
	else
		executor(cmd, env, &exec);
}
