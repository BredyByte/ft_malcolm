/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 13:33:37 by dbredykh          #+#    #+#             */
/*   Updated: 2023/05/30 18:53:51 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t		i;
	char		*s1ptr;
	char		*s2ptr;

	if (!*s2)
		return ((char *)s1);
	while (len-- && *s1)
	{
		if (*s1 == *s2)
		{
			i = len;
			s1ptr = (char *)s1 + 1;
			s2ptr = (char *)s2 + 1;
			while (i-- && *s1ptr && *s2ptr && *s1ptr == *s2ptr)
			{
				++s1ptr;
				++s2ptr;
			}
			if (*s2ptr == '\0')
				return ((char *)s1);
		}
		++s1;
	}
	return (0);
}
