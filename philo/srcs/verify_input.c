/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:33:14 by lhojoon           #+#    #+#             */
/*   Updated: 2024/06/04 19:24:19 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_strlen(const char *s)
{
	const char	*sp;

	sp = s;
	while (*sp)
	{
		sp++;
	}
	return (sp - s);
}

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n && *s1 && (*s1 == *s2))
	{
		++s1;
		++s2;
		--n;
	}
	if (n == 0)
	{
		return (0);
	}
	else
	{
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
	}
}

bool	check_input(const char *input)
{
	const char	*p;
	size_t		len;

	p = input;
	while (*p)
	{
		if (*p < '0' || *p > '9')
			return (false);
		p++;
	}
	len = ft_strlen(input);
	if (len > 10)
		return (false);
	if (len < 10)
		return (true);
	if (ft_strncmp(input, "2147483647", 10) > 0)
		return (false);
	return (true);
}
