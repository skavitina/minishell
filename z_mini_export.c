/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_mini_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnochiza <fnochiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:29:07 by fnochiza          #+#    #+#             */
/*   Updated: 2022/09/06 20:57:33 by fnochiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export_error(char *str)
{
	if (str)
	{
		ft_putstr_fd("ḾĪŇĪŠĤĚĹĹ ⟹  : export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": not a valid identifier", 2);
	}
}

static char	**array_from_string(char *str, char **array)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	while (str[i] != '=' && str[i] != '+')
		i++;
	if (str[i] == '+' && str[i + 1] != '=')
	{
		print_export_error(str);
		return (NULL);
	}
	array[0] = ft_substr(str, 0, i);
	if (str[i] == '+')
	{
		array[1] = ft_strdup("+=");
		i++;
	}
	else if (str[i] == '=')
		array[1] = ft_strdup("=");
	array[2] = ft_substr(str, i + 1, len - i - 1);
	array[3] = NULL;
	return (array);
}

static char	**split_for_export(char *str)
{
	char	**var;

	var = malloc(sizeof(char *) * 4);
	if (!var)
		return (NULL);
	if (ft_strchr(str, '='))
		var = array_from_string(str, var);
	else
	{
		var[0] = str;
		var[1] = NULL;
		var[2] = NULL;
		var[3] = NULL;
	}
	return (var);
}

static int	check_arg_of_export(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '_')
		return (1);
	if (ft_isalpha(str[0]))
		return (1);
	return (0);
}

int	ft_export(t_cmd *cmd, t_envp **envp_list)
{
	int		i;
	char	**array;

	i = -1;
	if (!envp_list || !cmd)
		return (1);
	if (!cmd->arg)
		return (print_env_declare(*envp_list));
	while (cmd->arg[++i])
	{
		if (check_arg_of_export(cmd->arg[i]))
		{
			array = split_for_export(cmd->arg[i]);
			if (!array)
				return (1);
			add_var_to_envp_list(envp_list, array, cmd->arg[i]);
			free_array(array);
		}
		else
		{
			print_export_error(cmd->arg[i]);
			return (1);
		}
	}
	return (0);
}
