/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_getstatus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 17:31:36 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/14 17:31:47 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t		ft_blocks_info(void const *ptr)
{
	long long int	x;
	t_block			*block_tmp;

	x = (long long int)ptr;
	x -= sizeof(t_block);
	if (x < (long long int)sizeof(t_zones))
		return (-1);
	block_tmp = (void*)ptr - sizeof(t_block);
	ft_putstr("0x10");
	ft_putbase((long long int)ptr, 16);
	ft_putstr(" - ");
	ft_putnbr(block_tmp->size);
	ft_putendl(" bytes");
	return (block_tmp->size);
}
