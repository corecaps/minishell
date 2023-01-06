/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:22:00 by latahbah          #+#    #+#             */
/*   Updated: 2022/12/22 16:44:18 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static size_t	ft_strlen(const char *s)
{
	unsigned int	res;

	res = 0;
	while (s[res] != 0)
		res ++;
	return (res);
}

char	*ft_strdup(char *src)
{
	int		size;
	char	*dest;
	int		pos;

	pos = 0;
	size = ft_strlen (src);
	dest = malloc(sizeof(char) * (size + 1));
	if (dest != NULL)
	{
		while (*(src + pos) != '\0')
		{
			*(dest + pos) = *(src + pos);
			pos ++;
		}
		*(dest + pos) = '\0';
	}
	return (dest);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			pos;
	unsigned char	*s;
	unsigned char	*d;

	s = (unsigned char *) src;
	d = (unsigned char *) dest;
	if (!s && !d)
		return (NULL);
	pos = 0;
	if (n == 0)
		return (dest);
	while (pos < n)
	{
		d[pos] = s[pos];
		pos ++;
	}
	return (dest);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_size;

	src_size = ft_strlen(src);
	if (src_size < size)
		ft_memcpy(dest, src, src_size + 1);
	else if (size)
	{
		ft_memcpy(dest, src, size - 1);
		dest[size - 1] = '\0';
	}
	return (ft_strlen(src));
}


static char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	len_s1;
	size_t	len_s2;
	size_t	pos;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	result = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (result == NULL)
		return (NULL);
	pos = 0;
	while (pos < (len_s1 + len_s2 + 1))
	{
		if (pos < len_s1)
			result[pos] = s1[pos];
		else
			result[pos] = s2[pos - len_s1];
		pos ++;
	}
	result[len_s1 + len_s2] = '\0';
	return (result);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	size;

	if (s == NULL)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start)
	{
		result = ft_strdup("");
		return (result);
	}
	size = ft_strlen(s + start);
	if (size < len)
		len = size;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s + start, len + 1);
	return (result);
}

static int	start_expantion(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '$')
	{
		if (str[i] == '\0')
			return (-1);
		i++;
	}
	return (i);
}

static int	end_expantion(char *str, int start)
{
	int	j;

	j = start;
	while (str[j] != ' ' && str[j] != '|'
		&& str[j] != '>' && str[j] != '<'
		&& str[j] != '\'' && str[j] != '\"'
		&& str[j] != '\0')
		j++;
	return (j);
}

char	*expand(char *str)
{
	int		i;
	int		j;
	char	*result;
	char	*value;
	char	*tmp;

	i = start_expantion(str);
	if (i == -1)
		return (str);
	j = end_expantion(str, i);
	tmp = ft_substr(str, i + 1, j - (i + 1));
	value = getenv(tmp);
	if (value == NULL)
		value = "";
	free(tmp);
	result = ft_substr(str, 0, (size_t)i);
	tmp = result;
	result = ft_strjoin(result, value);
	free(tmp);
	value = ft_substr(str, j, ft_strlen(str) - (size_t)j);
	tmp = result;
	result = ft_strjoin(result, value);
	free(tmp);
	free(value);
	return (result);
}

int	main(void)
{
	char	*str[10];
	int		i = 0;

	str[0] = "$A -la";
	str[1] = "lol";
	str[2] = "$";
	str[3] = "$A\"lll";
	str[4] = "$ss\'";
	str[5] = "$$$";
	str[6] = "$|";
	str[7] = "$<<";
	printf("======> Expander test <======\n");
	while (i < 8)
	{
		printf("Test %d:\n", i + 1);
		printf("Given str - [%s]\n", str[i]);
		printf("Expanded str - [%s]\n\n", expand(str[i]));
		i++;
	}
	return (0);
}
