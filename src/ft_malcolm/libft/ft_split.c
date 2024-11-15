/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:55:53 by dbredykh          #+#    #+#             */
/*   Updated: 2023/04/27 12:36:42 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_freeresult(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

static int	ft_count_words(const char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str != c)
		{
			count++;
			while (*str && *str != c)
				str++;
		}
		else
			str++;
	}
	return (count);
}

static char	*ft_copy_word(const char *str, char c)
{
	size_t	len;
	char	*word;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	word = ft_substr(str, 0, len);
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		num_words;
	int		i;

	num_words = ft_count_words(s, c);
	result = ft_calloc(num_words + 1, sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			result[i++] = ft_copy_word(s, c);
			if (!result[i - 1])
				return (ft_freeresult(result));
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (result);
}
