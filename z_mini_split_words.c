/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_mini_split_words.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnochiza <fnochiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:39:54 by fnochiza          #+#    #+#             */
/*   Updated: 2022/09/05 18:40:05 by fnochiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*write_redir(char *str, int *ind)
{
	char	*res;
	int		i;

	i = 0;
	if (str[i] == '>')
	{
		i++;
		if (str[i] == '>')
			i++;
	}
	else if (str[i] == '<')
	{
		i++;
		if (str[i] == '<')
			i++;
	}
	res = ft_substr(str, 0, i);
	*ind += i;
	return (res);
}

int	count_white_space(char *str)
{
	int	i;
	int	count_one;
	int	count_double;

	i = 0;
	count_one = 0;
	count_double = 0;
	while (i < (int)ft_strlen(str))
	{
		if (find_sep(str[i]) && count_one % 2 == 0 && count_double % 2 == 0)
			return (i);
		if (str[i] == '\'' && count_double % 2 == 0)
			count_one++;
		if (str[i] == '\"' && count_one % 2 == 0)
			count_double++;
		i++;
	}
	return (i);
}

char	*write_words(char *str, int *ind)
{
	t_words	*write_w;
	char	*result;

	write_w = init_write_w(str);
	while (write_w->i < write_w->len)
	{
		if (str[write_w->i] == '\'' && write_w->count_double % 2 == 0)
		{
			write_w->count_one++;
			write_w->i++;
		}
		if (str[write_w->i] == '\"' && write_w->count_one % 2 == 0)
			write_w->count_double++;
		else
			write_w->res[write_w->j++] = str[write_w->i];
		write_w->i++;
	}
	*ind += write_w->i;
	result = write_w->res;
	free(write_w);
	return (result);
}

static t_split	*split_by_w1(char *tmp, t_split *split_w)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tmp[i])
	{
		while (tmp[i] && ft_isspace(tmp[i]))
			i++;
		if (tmp[i] == '|')
			split_w->split_w[j++] = ft_substr(&tmp[i++], 0, 1);
		else if (tmp[i] == '<' || tmp[i] == '>')
			split_w->split_w[j++] = write_redir(&tmp[i], &i);
		else if (tmp[i + 1] && (!ft_strncmp(&tmp[i], "\'\'", 2)
				|| !ft_strncmp(&tmp[i], "\"\"", 2)))
			i += 2;
		else
			split_w->split_w[j++] = write_words(&tmp[i], &i);
	}
	split_w->split_w[j] = NULL;
	return (split_w);
}

char	**split_by_words(char *str)
{
	t_split	*split_w;
	char	*tmp;

	tmp = ft_strtrim(str, WHITE_SPACES);
	split_w = init_split(tmp);
	split_w = split_by_w1(tmp, split_w);
	ft_free(tmp);
	if (split_w)
		free(split_w);
	return (split_w->split_w);
}
