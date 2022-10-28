/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_mini_special_simbols.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnochiza <fnochiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:39:27 by fnochiza          #+#    #+#             */
/*   Updated: 2022/09/06 19:53:35 by fnochiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*subst_dollar(char *cmd, t_envp *envp_list)
{
	while (envp_list)
	{
		if (!ft_strncmp(cmd, envp_list->key, 1000))
			return (envp_list->value);
		envp_list = envp_list->next;
	}
	return ("");
}

static void	change_dollar(t_dollar *doll, char *str)
{
	char	*tmp_str;

	(void) str;
	doll->rez = ft_strjoin(doll->head, doll->cmd);
	tmp_str = doll->rez;
	doll->rez = ft_strjoin(doll->rez, doll->tail);
	str = doll->rez;
	ft_free(tmp_str);
	ft_free(doll->head);
	ft_free(doll->tail);
}

static char	*chng_doll(t_dollar *doll, char *str, int *num, t_envp *envp_list)
{
	int		n;
	int		i;
	t_envp	*tmp;
	char	*tmp_str;

	n = *num;
	doll->rez = ft_substr(str, 0, ft_strlen(str));
	tmp = envp_list;
	tmp_str = doll->rez;
	doll->head = ft_substr(doll->rez, 0, n);
	ft_free(tmp_str);
	i = n;
	while (str[i] && ft_isalnum(str[i + 2]))
		i++;
	doll->cmd = ft_substr(str, n + 1, i - n + 1);
	doll->tail = ft_substr(str, i + 2, ft_strlen(str));
	tmp_str = doll->cmd;
	doll->cmd = subst_dollar(doll->cmd, envp_list);
	ft_free(tmp_str);
	envp_list = tmp;
	change_dollar(doll, str);
	*num = 0;
	return (doll->rez);
}

static void	replace_d(t_dollar *doll, int *ind, char **str, t_envp *envp_list)
{
	int	i;

	i = *ind;
	if ((*str)[i + 1] && (*str)[i + 1] != '?')
	{
		doll->tmp = *str;
		*str = chng_doll(doll, *str, &i, envp_list);
		ft_free(doll->tmp);
		doll->count_one = 0;
		doll->count_double = 0;
	}
}

int	replace_dollar(char **str, t_envp *envp_list)
{
	t_dollar	*doll;
	int			i;

	i = 0;
	doll = init_doll();
	while ((*str)[i])
	{
		if ((*str)[i] == '<' && ((*str)[i + 1] && (*str)[i + 1] == '<'))
			dollar_redirect(*str, &i);
		if ((*str)[i] == '$' && doll->count_one % 2 == 0)
			replace_d(doll, &i, str, envp_list);
		if ((*str)[i] == '\'' && doll->count_double % 2 == 0)
			doll->count_one++;
		if ((*str)[i] == '\"' && doll->count_one % 2 == 0)
			doll->count_double++;
		i++;
	}
	free(doll);
	return (0);
}
