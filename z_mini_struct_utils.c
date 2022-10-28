/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_mini_struct_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnochiza <fnochiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:40:21 by fnochiza          #+#    #+#             */
/*   Updated: 2022/09/05 18:40:29 by fnochiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_copy_arr(char **arr_in, char **arr_out)
{
	int	i;

	i = 0;
	while (arr_out[i])
		i++;
	arr_in = malloc(sizeof(char *) * i + 1);
	arr_in[i] = NULL;
	i = -1;
	while (arr_out[++i])
		arr_in[i] = ft_substr(arr_out[i], 0, ft_strlen(arr_out[i]));
}

int	ft_n_words(char **arr, int i)
{
	int	n;

	n = 0;
	while (arr[i] && !ft_isdelim(arr[i++]))
		n++;
	return (n);
}

void	ft_empty_arr(char ***tmp, char *str)
{
	*tmp = (char **)malloc(sizeof(char *) * 2);
	(*tmp)[0] = ft_substr(str, 0, ft_strlen(str));
	ft_free(str);
	(*tmp)[1] = NULL;
}

static void	add_str(char ***arr, char *str)
{
	char	**tmp;
	int		i;

	i = 0;
	if (*arr)
	{
		while ((*arr)[i])
			i++;
		tmp = malloc(sizeof(char *) * (i + 2));
		tmp[i + 1] = NULL;
		tmp[0] = ft_substr(str, 0, ft_strlen(str));
		ft_free(str);
		i = 0;
		while ((*arr)[i])
		{
			tmp[i + 1] = ft_substr((*arr)[i], 0, ft_strlen((*arr)[i]));
			ft_free((*arr)[i]);
			i++;
		}
	}
	else
		ft_empty_arr(&tmp, str);
	free(*arr);
	*arr = tmp;
}

void	ft_one_name(t_cmd **cmd)
{
	t_cmd	*tmp;
	int		first_name;

	tmp = *cmd;
	first_name = 1;
	while ((*cmd))
	{
		if (first_name && (*cmd)->name != NULL)
			first_name = 0;
		else
		{
			add_str(&(*cmd)->arg, (*cmd)->name);
			(*cmd)->name = NULL;
		}
		if ((*cmd)->redir == 1)
			first_name = 1;
		(*cmd) = (*cmd)->next;
	}
	*cmd = tmp;
}
