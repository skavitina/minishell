/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_mini_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnochiza <fnochiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:25:48 by fnochiza          #+#    #+#             */
/*   Updated: 2022/09/06 20:12:53 by fnochiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	envp_add_to_end(t_envp *lst, t_envp *new)
{
	t_envp	*unit;

	unit = lst;
	while (unit->next != NULL)
		unit = unit->next;
	unit->next = new;
}

int	ft_env(t_envp *envp_list)
{
	if (!envp_list)
		return (1);
	while (envp_list)
	{
		ft_putstr_fd(envp_list->key, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(envp_list->value, 1);
		envp_list = envp_list->next;
	}
	return (0);
}
