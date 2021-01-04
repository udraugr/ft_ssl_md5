/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_argv_from_stdin.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 21:03:10 by udraugr-          #+#    #+#             */
/*   Updated: 2021/01/04 22:13:03 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ssl.h"

static size_t		g_j = 0;

static void			quote_case(char *str, size_t *i,
								size_t *begin, uint8_t *whitespaces)
{
	char			quote;
	size_t			j;

	j = *i;
	quote = str[j];
	*begin = (*whitespaces) ? j : *begin;
	*whitespaces = 0;
	ft_memmove(&str[j], &str[j + 1], ft_strlen(&str[j + 1]) + 1);
	++j;
	while (str[j] && str[j] != quote)
		++j;
	if (str[j])
		ft_memmove(&str[j], &str[j + 1], ft_strlen(&str[j + 1]) + 1);
	*i = j;
}

static void			letter_case(char *str, size_t *i,
								size_t *begin, uint8_t *whitespaces)
{
	size_t			j;

	j = *i;
	*begin = (*whitespaces) ? j : *begin;
	*whitespaces = 0;
	++j;
	while (str[j] && !ft_strchr(" \t\n\'\"", str[j]))
		++j;
	*i = j;
}

static void			word_loop(char *str, size_t word, char **args)
{
	size_t			i;
	size_t			begin;
	uint8_t			whitespaces;

	i = 0;
	begin = 0;
	whitespaces = 1;
	while (str[i] && g_j < word)
	{
		if (str[i] && ft_strchr(" \t\n", str[i]))
		{
			if (!(args[g_j++] = ft_strndup(&str[begin], &str[i] - &str[begin])))
				ft_exit_malloc_crash();
			++i;
			whitespaces = 1;
		}
		if (str[i] == '\'' || str[i] == '\"')
			quote_case(str, &i, &begin, &whitespaces);
		else
			letter_case(str, &i, &begin, &whitespaces);
	}
	if (!whitespaces &&
			!(args[g_j++] = ft_strndup(&str[begin], &str[i] - &str[begin])))
		ft_exit_malloc_crash();
}

char				**parse_argv_from_stdin(char *str)
{
	char			**args;
	size_t			word;

	args = NULL;
	word = word_count_argv_from_stdin(str);
	if (!(args = (char **)malloc(sizeof(char *) * (word + 1))))
		ft_exit_malloc_crash();
	g_j = 0;
	word_loop(str, word, args);
	args[g_j] = NULL;
	return (args);
}
