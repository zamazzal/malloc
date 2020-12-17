/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tobase.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 12:29:25 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/13 12:30:22 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	digit_count_base(long int number, int base)
{
	size_t		len;

	len = 0;
	while (number)
	{
		number /= base;
		len++;
	}
	return (len);
}

static void		print_converted_base(size_t len, int value, int sign, int base)
{
	static	char	bases[] = "0123456789abcdef";
	char			ptr[len + 1];

	ptr[len--] = '\0';
	if (sign)
		ptr[0] = '-';
	while (value != 0)
	{
		ptr[len] = bases[value % base];
		value = value / base;
		len--;
	}
	ft_putstr(ptr);
}

void			ft_putbase(int value, int base)
{
	size_t	len;
	int		sign;

	sign = 0;
	if (value == 0)
	{
		ft_putnbr(0);
		return ;
	}
	if (value < 0)
	{
		value *= -1;
		sign = (base == 10) ? 1 : 0;
	}
	len = digit_count_base(value, base);
	len += (sign ? 1 : 0);
	print_converted_base(len, value, sign, base);
	return ;
}
