/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_mini_ft_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnochiza <fnochiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:31:34 by fnochiza          #+#    #+#             */
/*   Updated: 2022/09/05 18:31:45 by fnochiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_nw(char const *s, char c)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			n++;
		while (s[i] && (s[i] != c))
			i++;
	}
	return (n);
}

static int	ft_lw(char const *s, char c)
{
	int	lw;
	int	i;

	lw = 0;
	i = 0;
	while (s[i] != c && s[i])
	{
		lw++;
		i++;
	}
	return (lw);
}

static void	*ft_1free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

static char	*ft_word(char const *s, char c, char **s1)
{
	int		i;
	int		x;
	char	*w;

	i = 0;
	x = 0;
	w = malloc(sizeof (char ) * (ft_lw(s, c) + 1));
	if (w == NULL)
		return (ft_1free(s1));
	while (s[i] && s[i] != c)
	{
		w[x] = s[i];
		x++;
		i++;
	}
	w[x] = '\0';
	return (w);
}

char	**ft_split(char const *s, char c)
{
	char	**s1;
	int		i;
	int		x;

	i = 0;
	x = 0;
	if (!s)
		return (NULL);
	s1 = malloc(sizeof (char *) * (ft_nw(s, c) + 1));
	if (s1 == NULL)
		return (NULL);
	while (s[x])
	{
		while (s[x] && s[x] == c)
			x++;
		if (s[x] && s[x] != c)
		{
			s1[i] = ft_word(s + x, c, s1);
			x = x + ft_lw(s + x, c);
			i++;
		}
	}
	s1[i] = NULL;
	return (s1);
}
