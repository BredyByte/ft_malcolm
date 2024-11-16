/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:28:22 by dbredykh          #+#    #+#             */
/*   Updated: 2023/04/21 16:50:06 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[i] && i < len)
		i++;
	while (src[j] && (i + j + 1) < len)
	{
		dest[i + j] = src[j];
		j++;
	}
	if (i < len)
		dest[i + j] = '\0';
	return (i + ft_strlen(src));
}
