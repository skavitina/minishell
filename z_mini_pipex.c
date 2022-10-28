/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_mini_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnochiza <fnochiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:37:08 by fnochiza          #+#    #+#             */
/*   Updated: 2022/09/05 18:37:37 by fnochiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_proc(t_cmd *cmd, t_envp **env, t_exec *exec, int *pipefd)
{
	if ((cmd->next || cmd->redir == 1) && cmd->redir != 4)
	{
		close(1);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		close(pipefd[0]);
	}
	redirect_handler(cmd, pipefd);
	executor(cmd, env, exec);
	exit(g_exit_status);
}

void	pipex(t_cmd *cmd, t_envp **env, t_exec *exec)
{
	int	pid;
	int	pipefd[2];
	int	exit_status;

	if (cmd->redir != 0)
		pipe(pipefd);
	pid = fork();
	if (pid == 0)
		child_proc(cmd, env, exec, pipefd);
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
	close (0);
	pipe_close(cmd, pipefd[0], pipefd[1]);
}

void	pipe_handler(t_cmd *cmd, t_envp **env, t_exec *exec)
{
	int		save_stdout;
	int		i;
	t_cmd	*tmp;

	save_stdout = dup(0);
	tmp = cmd;
	i = 0;
	while (tmp && i <= exec->pipe_num)
	{
		pipex(tmp, env, exec);
		if ((exec->pipe_num) > 0)
		{
			if (tmp->redir && tmp->redir != 1)
			{
				while (tmp->redir && tmp->redir != 1 && tmp->next)
					tmp = tmp->next;
				if (tmp->redir == 1 && !tmp->name)
					tmp = tmp->next;
			}
			else
				tmp = tmp->next;
		}
		i++;
	}
	std_out_close(save_stdout);
}
