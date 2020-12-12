/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 18:13:33 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/12 18:14:43 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		ft_show_zone(t_zones *zone)
{
	if (zone->zone_type == TINY)
		ft_putstr("TINY: ");
	else if (zone->zone_type == SMALL)
		ft_putstr("SMALL: ");
	else
		ft_putstr("LARGE: ");
	printf("%p\n", zone); // remove this
}

static void		ft_show_block(void *ptr, size_t len)
{
	static size_t total = 0;

	total += len;
	printf("%p - %p: %ld bytes\n", ptr, ptr + len, len); // remove this
}

static size_t	show_block_mem(void *ptr, long long	int *x)
{
	t_block *block_ptr;

	block_ptr = ptr + *x;
	if (block_ptr && block_ptr->size >= 1)
	{
		*x = *x + sizeof(t_block) + block_ptr->size;
		if (block_ptr->alc == IS_ALLOCATED)
		{
			ft_show_block(block_ptr + sizeof(t_block), block_ptr->size);
			return (block_ptr->size);
		}
	}
	else
		(*x)++;
	return (0);
}

void			show_alloc_mem(void)
{
	t_zones			*tmp;
	long long int	x;
	size_t			rzlt;
	static size_t	total;

	total = 0;
	tmp = g_zones_list;
	while (tmp != NULL)
	{
		ft_show_zone(tmp);
		x = sizeof(t_zones);
		while (x - 1 < tmp->size)
		{
			rzlt = show_block_mem(tmp, &x);
			total += rzlt;
			if (rzlt && tmp->zone_type == LARGE)
				break ;
		}
		tmp = tmp->next;
	}
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putendl(" bytes");
}
