/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:33:08 by jgarcia           #+#    #+#             */
/*   Updated: 2022/05/23 12:23:46 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	clean(char **s, size_t size)
{
	size_t	pos;

	pos = 0;
	while (pos < size)
		free(s[pos]);
	return (-1);
}

static size_t	count_words(const char *s, char c)
{
	size_t	pos;
	size_t	words;

	words = 0;
	pos = 0;
	while (s[pos])
	{
		if ((s[pos + 1] == c || s[pos + 1] == '\0')
			&& !(s[pos] == c || s[pos] == '\0'))
			words++;
		pos++;
	}
	return (words);
}

static int	fill(char **result, const char *s, char c)
{
	size_t	pos;
	size_t	s_pos;
	size_t	word;

	word = 0;
	pos = 0;
	while (s[pos])
	{
		if (s[pos] == c || s[pos] == '\0')
			pos++;
		else
		{
			s_pos = 0;
			while (!(s[pos + s_pos] == c || s[pos + s_pos] == '\0'))
				s_pos++;
			result[word] = ft_substr(s + pos, 0, s_pos);
			if (result[word] == NULL)
				return (clean(result, word - 1));
			pos += s_pos;
			word++;
		}
	}
	return (0);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	result = (char **) malloc(sizeof(char *) * (words + 1));
	if (result == NULL)
		return (NULL);
	result[words] = 0;
	if (fill(result, s, c) == -1)
		return (NULL);
	return (result);
}
