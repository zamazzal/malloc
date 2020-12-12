/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_zone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 20:14:38 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/12 20:15:29 by zamazzal         ###   ########.fr       */
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
	g_zones_list = ft_addinlist(zone);
}

void			*create_new_zone(size_t size, int type)
{
	void	*ptr;
	size_t	len;
	t_zones	*new_zone;
	t_block	*new_block;

	len = ft_getlen(type);
	new_zone = mmap(NULL, len
	, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, 0, 0);
	if (new_zone == MAP_FAILED)
		return (NULL);
	ft_bzero(new_zone, len);
	new_zone->zone_type = type;
	new_zone->size = len;
	new_zone->next = NULL;
	new_block = (void*)new_zone + sizeof(t_zones);
	new_block->size = size;
	new_block->alc = IS_ALLOCATED;
	prepare_nzone(new_zone, size, len, type);
	return (new_block + sizeof(t_block));
}

void			*alloc_large_zone(size_t size)
{
	void	*ptr;
	size_t	len;
	t_zones	*new_zone;
	t_block	*new_block;

	len = multipleof_pages(size);
	new_zone = mmap(NULL, len
	, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, 0, 0);
	if (new_zone == MAP_FAILED)
		return (NULL);
	ft_bzero(new_zone, len);
	new_zone->zone_type = LARGE;
	new_zone->size = len;
	new_zone->next = NULL;
	new_block = (void*)new_zone + sizeof(t_zones);
	new_block->size = size;
	new_block->alc = IS_ALLOCATED;
	g_zones_list = ft_addinlist(new_zone);
	return (new_block + sizeof(t_block));
}
