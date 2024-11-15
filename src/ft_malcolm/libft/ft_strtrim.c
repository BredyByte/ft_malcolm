/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:09:25 by dbredykh          #+#    #+#             */
/*   Updated: 2023/04/26 16:27:32 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_set_contain(char c, char const *set)
{
	while (*set)
	{
		if (*set++ == c)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	int		start;
	int		end;
	int		i;

	if (s1 == 0 || set == 0)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_set_contain(s1[start], set))
		start++;
	while (end > start && ft_set_contain(s1[end - 1], set))
		end--;
	dest = malloc(sizeof(char) * (end - start + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (start < end)
		dest[i++] = s1[start++];
	dest[i] = '\0';
	return (dest);
}
