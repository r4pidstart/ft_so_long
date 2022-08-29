/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 03:47:43 by tjo               #+#    #+#             */
/*   Updated: 2022/08/30 04:16:10 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"./ft_libft.h"

static int	my_isspace(int c)
{
	return ((9 <= c && c <= 13) || c == 20 || c == 32);
}

static int	my_issign(int c)
{
	return ('+' == c || '-' == c);
}

int	ft_atoi(const char *str)
{
	char		*cur;
	int			minus_cnt;
	long long	ret;

	cur = (char *)str;
	while (my_isspace(*cur))
		cur++;
	ret = 0;
	minus_cnt = 0;
	if (my_issign(*cur))
	{
		if (*cur == '-')
			minus_cnt++;
		cur++;
	}
	while ('0' <= *cur && *cur <= '9')
		ret = ret * 10 + (*(cur++) - '0');
	if (minus_cnt)
		ret *= -1;
	return (ret);
}

int	get_length(long long n)
{
	int	ret;

	ret = 0;
	if (n == 0)
		ret++;
	if (n < 0)
	{
		ret++;
		n *= -1;
	}
	while (n)
	{
		ret++;
		n /= 10;
	}
	return (ret);
}

char	*ft_itoa(int n)
{
	long long	tmp;
	char		*ret;
	int			cur;

	ret = (char *)malloc(sizeof(char) * get_length(n) + 1);
	if (!ret)
		return (0);
	tmp = n;
	cur = 0;
	if (n < 0)
	{
		ret[cur++] = '-';
		tmp *= -1;
	}
	if (n == 0)
		ret[cur++] = '0';
	cur = get_length(n);
	ret[cur] = '\0';
	while (tmp)
	{
		ret[--cur] = tmp % 10 + '0';
		tmp /= 10;
	}
	return (ret);
}
