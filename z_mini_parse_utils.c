/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_mini_parse_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnochiza <fnochiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:36:20 by fnochiza          #+#    #+#             */
/*   Updated: 2022/09/05 18:36:29 by fnochiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdelim(char *s)
{
	if (!ft_strncmp(s, "|", 1) || !ft_strncmp(s, "<", 1) || \
		!ft_strncmp(s, ">", 1) || !ft_strncmp(s, "<<", 2) || \
		!ft_strncmp(s, ">>", 2))
		return (1);
	else
		return (0);
}

int	delimetr(char *s)
{
	if (s[0] == '|')
		return (1);
	if (s[0] == '<' && s[1] == '\0')
		return (2);
	if (s[0] == '>' && s[1] == '\0')
		return (3);
	if (s[0] == '<' && s[1] == '<')
		return (4);
	if (s[0] == '>' && s[1] == '>')
		return (5);
	return (0);
}

void	dollar_redirect(char *str, int *num)
{
	int	i;

	i = *num + 2;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '$')
	{
		i++;
		while (str[i] && ft_isalnum(str[i + 2]))
			i++;
	}
	*num = i;
}

void	make_struct(char **arr, int *ind, t_cmd **new)
{
	int	i;

	i = *ind;
	if (ft_isdelim(arr[i]) && arr[i][0] != '|')
	{
		*new = com_new1(NULL, NULL, delimetr(arr[i]), arr[i + 1]);
		i += 2;
	}
	else if (ft_isdelim(arr[i]) && arr[i][0] == '|')
	{
		*new = com_new1(0, 0, 1, 0);
		i++;
	}
	else
		i = ft_new_cmd(i, arr, new);
	*ind = i;
}
