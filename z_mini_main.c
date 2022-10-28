/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_mini_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnochiza <fnochiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:33:52 by fnochiza          #+#    #+#             */
/*   Updated: 2022/09/06 20:34:29 by fnochiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_args(int argc, char **argv)
{
	if (argc > 1)
	{
		ft_putstr_fd("ḾĪŇĪŠĤĚĹĹ ⟹  : ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit(127);
	}
}

void	parse_and_execute(t_envp **envp_list, t_cmd *cmd, char **split_words,
							char *read_str)
{
	if (ft_strlen(read_str) > 0)
	{
		add_history(read_str);
		if (!check_syntax(read_str))
		{
			replace_dollar(&read_str, *envp_list);
			split_words = split_by_words(read_str);
			if (split_words != NULL && split_words[0] != NULL)
			{
				if (check_double_delim(split_words))
					ft_putendl_fd("syntax error near \
									unexpected token `newline'", 2);
				ft_struct(split_words, &cmd);
				if (cmd)
					execute(cmd, envp_list);
			}
		}
		handle_signals2();
		ft_free_com_list(&cmd);
		free_array(split_words);
		free(read_str);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	**split_words;
	t_envp	*envp_list;
	t_cmd	*cmd;
	char	*read_str;

	check_args(argc, argv);
	g_exit_status = 0;
	split_words = NULL;
	envp_list = NULL;
	cmd = NULL;
	read_envp(env, &envp_list);
	while (1)
	{
		handle_signals();
		read_str = read_line();
		handle_signals2();
		parse_and_execute(&envp_list, cmd, split_words, read_str);
	}
	rl_clear_history();
	return (0);
}
