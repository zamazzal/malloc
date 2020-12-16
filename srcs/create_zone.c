/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_zone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 20:14:38 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/13 13:59:42 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_zones	*ft_addinlist(t_zones *new_zone)
{
	t_zones		*tmp;

	if (g_zones_list == NULL)
		return (new_zone);
	tmp = g_zones_list;
	while (g_zones_list->next != NULL)
		g_zones_list = g_zones_list->next;
	g_zones_list->next = new_zone;
	g_zones_list = tmp;
	return (g_zones_list);
}

static void		prepare_nzone(void *zone, size_t size, size_t len, int type)
{
	t_block	*new_block2;
	size_t	x;
	size_t	space;

	x = sizeof(t_zones) + sizeof(t_block) + size;
	space = get_size_bytype(type);
	while (x + 1 < len)
	{
		new_block2 = (void*)zone + x;
		new_block2->size = space;
		new_block2->alc = 0;
		x += sizeof(t_block) + space;
	}
}

static	void	*create_zone_mmap(size_t len, int type, size_t size)
{
	t_zones	*new_zone;
	t_block	*new_block;
	void	*ptr;

	new_zone = mmap(NULL, len
	, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (new_zone == MAP_FAILED)
		return (NULL);
	ft_bzero(new_zone, len);
	new_zone->zone_type = type;
	new_zone->size = len;
	new_zone->next = NULL;
	new_block = (void*)new_zone + sizeof(t_zones);
	new_block->size = size;
	new_block->alc = IS_ALLOCATED;
	ptr = (void*)new_block + sizeof(t_block);
	return (ptr);
}

void			*create_new_zone(size_t size, int type)
{
	size_t	len;
	void	*ptr;
	t_zones	*zone;

	len = ft_getlen(type);
	ptr = create_zone_mmap(len, type, size);
	if (!ptr)
		return (NULL);
	zone = ptr - (sizeof(t_block) + sizeof(t_zones));
	prepare_nzone(zone, size, len, type);
	g_zones_list = ft_addinlist(zone);
	return (ptr);
}

void			*alloc_large_zone(size_t size)
{
	size_t	len;
	void	*ptr;
	t_zones	*zone;

	len = multipleof_pages(size);
	ptr = create_zone_mmap(len, LARGE, size);
	if (!ptr)
		return (NULL);
	zone = ptr - (sizeof(t_block) + sizeof(t_zones));
	g_zones_list = ft_addinlist(zone);
	return (ptr);
}
