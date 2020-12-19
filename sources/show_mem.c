/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 18:13:33 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/19 04:42:01 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			ft_show_zone(t_zones *zone)
{
	if (zone->zone_type == TINY)
		ft_putstr("TINY: ");
	else if (zone->zone_type == SMALL)
		ft_putstr("SMALL: ");
	else
		ft_putstr("LARGE: ");
	ft_putstr("0x10");
	ft_putbase((long long int)zone, 16);
	ft_putchar('\n');
}

static void		ft_show_block(t_block *block)
{
	void *ptr;

	ptr = (void*)block + sizeof(t_block);
	ft_putstr("0x10");
	ft_putbase((long long int)ptr, 16);
	ft_putstr(" - ");
	ft_putstr("0x10");
	ft_putbase((long long int)ptr + block->size - 1, 16);
	ft_putstr(": ");
	ft_putnbr(block->size);
	ft_putendl(" bytes");
}

static void		show_alloc_mem_simple(void)
{
	t_zones			*tmp;
	size_t			total;
	t_block			*block;

	total = 0;
	tmp = g_zones_list;
	while (tmp != NULL)
	{
		ft_show_zone(tmp);
		block = (void*)tmp + sizeof(t_zones);
		while (block != NULL)
		{
			if (block && block->size >= 1 && block->alc == IS_ALLOCATED)
			{
				ft_show_block(block);
				total += block->size;
			}
			block = block->next;
		}
		tmp = tmp->next;
	}
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putendl(" bytes");
}

void			show_alloc_mem(void)
{
	pthread_mutex_lock(&g_lock);
	show_alloc_mem_simple();
	pthread_mutex_unlock(&g_lock);
}
