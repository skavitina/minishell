/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_mini_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnochiza <fnochiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:38:27 by fnochiza          #+#    #+#             */
/*   Updated: 2022/09/06 20:58:49 by fnochiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	left_redirect(t_cmd *cmd)
{
	int	output;

	output = 0;
	output = open(cmd->file, O_RDONLY);
	if (output == -1)
	{
		ft_putstr_fd("ḾĪŇĪŠĤĚĹĹ ⟹  : ", 2);
		ft_putstr_fd(cmd->file, 2);
		ft_putendl_fd(": No such file or directory", 2);
		g_exit_status = 126;
		return ;
	}
	dup2(output, 0);
	close(output);
}

void	right_redirect(t_cmd *cmd)
{
	int	output;

	output = 0;
	while (cmd->redir == 3 && cmd->file)
	{
		output = open(cmd->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (output == -1)
		{
			ft_putstr_fd("ḾĪŇĪŠĤĚĹĹ ⟹  : ", 2);
			ft_putstr_fd(cmd->file, 2);
			ft_putendl_fd(": Permission denied", 2);
			g_exit_status = 126;
			return ;
		}
		if (cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
	dup2(output, 1);
	close(output);
}

void	double_right_redirect(t_cmd *cmd)
{
	int	output;

	output = 0;
	while (cmd->redir == 5 && cmd->file)
	{
		output = open(cmd->file, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (output == -1)
		{
			ft_putstr_fd("ḾĪŇĪŠĤĚĹĹ ⟹  : ", 2);
			ft_putstr_fd(cmd->file, 2);
			ft_putendl_fd(": Permission denied", 2);
			g_exit_status = 126;
			return ;
		}
		if (cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
	dup2(output, 1);
	close(output);
}

void	redirect_handler(t_cmd *cmd, int *pipefd)
{
	int	output;

	output = 0;
	if (cmd->redir == 2)
		left_redirect(cmd);
	if (cmd->redir == 3)
		right_redirect(cmd);
	if (cmd->redir == 5)
		double_right_redirect(cmd);
	if (cmd->redir == 4)
	{
		output = heredoc(cmd);
		dup2(output, 0);
		close(output);
		if (cmd->next && cmd->next->redir == 1)
		{
			close(1);
			dup2(pipefd[1], 1);
			close(pipefd[1]);
			close(pipefd[0]);
		}
	}
}
