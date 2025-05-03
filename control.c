/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:36:46 by yozlu             #+#    #+#             */
/*   Updated: 2025/05/02 19:40:31 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	count;

	i = 0;
	count = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		count = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	result = 0;
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * count);
}

int check(char **str)
{
    int i;
	int j;
    i = 1;
    while (str[i])
    {
		j = 0;
		while (str[i][j])
		{
			if(ft_isdigit(str[i][j]) == 0)
			{
            	return -1;
			}
			j++;
		}
        i++;    
    }
    i = 1;
    while (str[i])
    {
        if (ft_atoi(str[i]) <= 0 || ft_atoi(str[0]) > 200)
		{
			return -1;
		}	
		i++;
    }
    return 0;
}