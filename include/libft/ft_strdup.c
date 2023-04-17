/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 13:01:33 by belkarto          #+#    #+#             */
/*   Updated: 2023/04/17 05:08:53 by ohalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)ft_calloc(sizeof(char), ft_strlen(s1) + 1);
	if (!str)
		return (0);
	while (i <= ft_strlen(s1))
	{
		str[i] = '\0';
		i++;
	}
	ft_memcpy(str, s1, ft_strlen(s1));
	return (str);
}
