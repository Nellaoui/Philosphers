/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:05:32 by nelallao          #+#    #+#             */
/*   Updated: 2023/05/22 14:57:55 by nelallao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// static int	counter(const char *s, char c)
// {
// 	int	i;
// 	int	n;

// 	n = 0;
// 	i = 0;
// 	while (s[i])
// 	{
// 		while (s[i] == c)
// 			i++;
// 		if (s[i])
// 		{
// 			while (s[i] && s[i] != c)
// 				i++;
// 			n++;
// 		}
// 	}
// 	return (n);
// }

// static int	w_len(const char *s, char c)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i] && s[i] != c)
// 		i++;
// 	return (i);
// }

// char	**ft_split(char *s, char c)
// {
// 	char	**dest;
// 	int		j;
// 	int		k;

// 	dest = (char **)ft_calloc((counter(s, c) + 1), (sizeof(char *)));
// 	if (!dest)
// 		return (0);
// 	j = 0;
// 	while (*s)
// 	{
// 		while (*s == c)
// 			s++;
// 		if (*s)
// 		{
// 			dest[j] = (char *)malloc((w_len(s, c) + 1) * (sizeof(char)));
// 			if (!dest[j])
// 				return (0);
// 			k = 0;
// 			while (*s && *s != c)
// 				dest[j][k++] = *s++;
// 			dest[j++][k] = '\0';
// 		}
// 	}
// 	dest[j] = 0;
// 	return (dest);
// }

int	ft_isdigit(int n)
{
	if (n >= '0' && n <= '9')
		return (1);
	else
		return (0);
}

long	ft_atoi(const char *str)
{
	long	signe;
	long	i;
	long	result;

	signe = 1;
	i = 0;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\f')
	{
		i++;
	}
	if (str[i] == '-')
	{
		signe = signe * (-1);
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * signe);
}

