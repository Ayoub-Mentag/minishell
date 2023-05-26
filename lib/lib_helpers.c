/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouaddi <ibouaddi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 00:14:06 by ibouaddi          #+#    #+#             */
/*   Updated: 2023/03/20 00:14:06 by ibouaddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	j;
	size_t	i;
	size_t	len_s;
	char	*dest;

	i = start;
	if (!s)
		return (0);
	len_s = ft_strlen((char *) s);
	if (start > len_s)
		return (ft_strdup(""));
	if (len > len_s)
		len = len_s;
	if (len_s - start < len)
		len = len_s - start;
	dest = (char *)ft_malloc(sizeof(char) *(len + 1));
	if (!dest)
		return (0);
	j = 0;
	while (i < len_s && j < len)
		dest[j++] = s[i++];
	dest[j] = '\0';
	return (dest);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!s1 || !s2)
		return (0);
	while (n > 0 && *s1 && *s2 && *(unsigned char *) s1 == *(unsigned char *)s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

static	int	number_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = number_len(n);
	str = (char *)ft_malloc(len + 1);
	if (str == NULL)
		return (NULL);
	if (n == -2147483648)
		ft_strlcpy(str, "-2147483648", 12);
	str[len--] = 0;
	if (n == 0)
		str[len] = '0';
	else if (n < 0)
	{
		str[0] = '-';
		n = n * (-1);
	}
	while (n > 0)
	{
		str[len--] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	len1;
	int	len2;
	int	i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 == len2)
		return (ft_strncmp(s1, s2, len1));
	i = 0;
	while ((s1[i] != 0 && s2[i] != 0) && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}
