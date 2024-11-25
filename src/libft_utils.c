#include "malcolm.h"

void	*ft_memcpy(void *dest, const void *src, size_t len) {
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!len || (!dest && !src))
		return (dest);
	while (len--)
		*d++ = *s++;
	return (dest);
}

void	ft_bzero(void *s, size_t n) {
	unsigned char	*new_str;

	new_str = (unsigned char *)s;
	while (n--)
		*new_str++ = '\0';
}

void	*ft_memset(void *b, int c, size_t len) {
	char	*p;

	p = (char *)b;
	while (len--)
		p[len] = c;
	return (b);
}

int ft_isxdigit(char c) {
    if (c >= '0' && c <= '9') {
        return 1;
    }
    if (c >= 'a' && c <= 'f') {
        return 1;
    }
    if (c >= 'A' && c <= 'F') {
        return 1;
    }
    return 0;
}

int	ft_memcmp(const void *s1, const void *s2, size_t n) {
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	if (n == 0)
		return (0);
	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (*str1 == *str2 && ++i < n)
	{
		str1++;
		str2++;
	}
	return ((int)(*str1 - *str2));
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

