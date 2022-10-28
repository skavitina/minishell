/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_mini_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnochiza <fnochiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:22:01 by fnochiza          #+#    #+#             */
/*   Updated: 2022/09/05 20:27:27 by fnochiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cut_tail_string(char *str)
{
	int	i;

	if (!str)
		return (NULL);
	i = ft_strlen(str);
	while (str[i] != '/')
		i--;
	return (ft_substr(str, 0, i + 1));
}

static int	home_directory(t_cmd *cmd, char *home)
{
	char	*tmp;

	if (!cmd->arg || !ft_strcmp(cmd->arg[0], "~"))
		chdir(home);
	else
	{
		if (!ft_strncmp(cmd->arg[0], "~/", 2))
		{
			tmp = cmd->arg[0] + 1;
			cmd->arg[0] = ft_strjoin(home, "/");
			cmd->arg[0] = ft_strjoin(cmd->arg[0], tmp);
		}
		else
		{
			tmp = cut_tail_string(home);
			cmd->arg[0] = ft_strjoin(tmp, cmd->arg[0] + 1);
			free(tmp);
		}
		chdir(cmd->arg[0]);
	}
	return (0);
}

static int	change_directory(t_cmd *cmd, char *home, char *pwd, char *old_pwd)
{
	char	*tmp;

	if (!cmd->arg || !ft_strncmp(cmd->arg[0], "~", 1))
		home_directory(cmd, home);
	else if (!ft_strcmp(cmd->arg[0], "."))
		chdir(pwd);
	else if (!ft_strcmp(cmd->arg[0], "-"))
	{
		chdir(old_pwd);
		ft_putendl_fd(old_pwd, 1);
	}
	else if (!ft_strcmp(cmd->arg[0], ".."))
	{
		tmp = cut_tail_string(pwd);
		chdir(tmp);
		free(tmp);
	}
	else
		chdir(cmd->arg[0]);
	return (0);
}

int	ft_cd(t_cmd *cmd, t_envp *envp_list)
{
	char	*home;
	char	*pwd;
	char	*old_pwd;

	if (!envp_list || !cmd)
		return (1);
	home = get_value_from_envp(envp_list, "HOME");
	pwd = get_value_from_envp(envp_list, "PWD");
	old_pwd = get_value_from_envp(envp_list, "OLDPWD");
	if (!home || !pwd || !old_pwd)
		return (1);
	change_directory(cmd, home, pwd, old_pwd);
	if (put_value_to_envp(envp_list, "OLDPWD", pwd))
		return (1);
	if (put_value_to_envp(envp_list, "PWD", getcwd(NULL, 0)))
		return (1);
	free(home);
	free(old_pwd);
	return (0);
}
