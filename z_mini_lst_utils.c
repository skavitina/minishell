/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_mini_lst_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnochiza <fnochiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:33:28 by fnochiza          #+#    #+#             */
/*   Updated: 2022/09/06 20:37:15 by fnochiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_line(void)
{
	char	*read_str;

	read_str = readline("ḾĪŇĪŠĤĚĹĹ ⟹  ");
	if (!read_str)
	{
		ft_putendl_fd("exit", 2);
		rl_clear_history();
		exit(1);
	}
	return (read_str);
}

void	read_envp(char **env, t_envp **envp_list)
{
	int		i;
	t_envp	*new;

	i = 0;
	*envp_list = envp_new(env[i++]);
	while (env[i])
	{
		new = envp_new(env[i++]);
		envp_add_to_end(*envp_list, new);
	}
}

t_envp	*envp_new(char *content)
{
	t_envp	*envp;
	int		len;
	int		i;

	i = 0;
	envp = malloc(sizeof(t_envp));
	if (!envp)
		return (NULL);
	len = ft_strlen(content);
	while (content[i] != '=')
		i++;
	envp->key = malloc(sizeof(char) * (i + 1));
	envp->value = malloc(sizeof(char) * (len - i + 1));
	if (!envp->key || !envp->value)
		return (NULL);
	ft_strlcpy(envp->key, content, i + 1);
	ft_strlcpy(envp->value, &content[i + 1], len - i);
	envp->next = NULL;
	return (envp);
}

void	envp_add_front(t_envp **lst, t_envp *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

void	cmd_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*elem;

	elem = *lst;
	if (elem)
	{
		while (elem->next)
			elem = elem->next;
		elem->next = new;
	}
	else
		*lst = new;
}
