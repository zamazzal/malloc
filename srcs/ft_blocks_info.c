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
	t_block			*block_tmp;

	block_tmp = ft_get_block(ptr);
	if (!block_tmp)
		return (-1);
	ft_putstr("0x10");
	ft_putbase((long long int)ptr, 16);
	ft_putstr(" - ");
	ft_putnbr(block_tmp->size);
	ft_putendl(" bytes");
	return (block_tmp->size);
}

size_t		ft_block_len(void const *ptr)
{
	t_block			*block_tmp;

	block_tmp = ft_get_block(ptr);
	if (!block_tmp)
		return (-1);
	return (block_tmp->size);
}
