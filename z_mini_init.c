/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_mini_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnochiza <fnochiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:32:59 by fnochiza          #+#    #+#             */
/*   Updated: 2022/09/06 18:41:19 by fnochiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_split	*init_split(char *str)
{
	t_split	*split_w;

	split_w = malloc(sizeof(t_split));
	split_w->words = count_words(str, 0, 0);
	split_w->split_w = (char **)malloc((split_w->words + 1) * sizeof(char *));
	if (!split_w->split_w)
		exit(1);
	return (split_w);
}

t_words	*init_write_w(char *str)
{
	t_words	*write_w;

	write_w = malloc(sizeof(t_words));
	write_w->count_one = 0;
	write_w->count_double = 0;
	write_w->j = 0;
	write_w->i = 0;
	write_w->len = count_white_space(str);
	write_w->res = malloc(sizeof(char *) * (write_w->len + 1));
	write_w->res[write_w->len] = '\0';
	if (!write_w->res)
		exit(1);
	return (write_w);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->name = NULL;
	cmd->arg = NULL;
	cmd->redir = 0;
	cmd->file = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_dollar	*init_doll(void)
{
	t_dollar	*doll;

	doll = malloc(sizeof(t_dollar));
	doll->tmp = NULL;
	doll->count_one = 0;
	doll->count_double = 0;
	doll->rez = NULL;
	doll->head = NULL;
	doll->cmd = NULL;
	doll->tail = NULL;
	return (doll);
}
