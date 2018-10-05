/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angonyam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 16:53:39 by angonyam          #+#    #+#             */
/*   Updated: 2017/06/03 05:41:13 by angonyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		digit_count(const char *str, int i)
{
	int count;

	count = 0;
	while (ft_isdigit(str[i]))
	{
		count++;
		i++;
	}
	return (count);
}

static int		ft_atoi_convert(const char *str, int i)
{
	int sum;

	sum = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			sum = (sum * 10) + (str[i] - '0');
		else
			break ;
		i++;
	}
	return (sum);
}

static int		ft_is_whitespace(const char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t' || str[i] == ' ' || str[i] == '\n' ||\
				str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
			i++;
		else
			break ;
	}
	return (i);
}

int				ft_atoi(const char *str)
{
	int i;
	int count;
	int neg;

	neg = 1;
	i = ft_is_whitespace(str);
	if (str[i] == '+')
		i++;
	else if (str[i] == '-' || str[i] == '0')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
		if (str[i] == '0')
			while (str[i] == '0')
				i++;
	}
	count = digit_count(str, i);
	i = ft_atoi_convert(str, i);
	if (count >= 19 && neg == 1)
		return (-1);
	if (count >= 19 && neg == -1)
		return (0);
	return (i * neg);
}
