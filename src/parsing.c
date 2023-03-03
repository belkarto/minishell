/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:32:49 by belkarto          #+#    #+#             */
/*   Updated: 2023/03/01 15:02:00 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"
#include <stdlib.h>

void	parsing_input(char *input)
{
	char *trim;

	if (input == NULL)
		end_of_file();
	trim = ft_strtrim(input, "\'");
	printf("%s\n", getenv(input));
	free(trim);
}
