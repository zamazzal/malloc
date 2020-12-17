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

static void		prepare_nzone(t_zones *zone)
{
	size_t	x;
	size_t	space;
    t_block *new_block;

    new_block = (void*)zone + sizeof(t_zones);
	x = sizeof(t_zones) + sizeof(t_block) + new_block->size;
	space = get_size_bytype(zone->zone_type);
	while (x + 1 < zone->size)
	{
		new_block = (void*)zone + x;
		new_block->size = space;
		new_block->alc = 0;
		x += sizeof(t_block) + space;
	}
}

static	void	*ft_mmap(size_t len)
{
	void	*ptr;

	ptr = mmap(NULL, len
	, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	ft_bzero(ptr, len);
	return (ptr);
}

static  void    *ft_create_block(void *ptr, int type, size_t size, size_t len)
{
    t_zones     *new_zone;
    t_block     *new_block;
    void        *new_ptr;

    new_zone = (void*)ptr;
    new_zone->zone_type = type;
	new_zone->size = len;
	new_zone->next = NULL;
	new_block = (void*)new_zone + sizeof(t_zones);
	new_block->size = size;
	new_block->alc = IS_ALLOCATED;
	new_ptr = ptr + sizeof(t_block) + sizeof(t_zones);
    return (new_ptr);
}

void			*create_new_zone(size_t size, int type)
{
	size_t	len;
	void	*ptr;
	t_zones	*zone;

	len = ft_getlen(type, size);
	zone = ft_mmap(len);
	if (!zone)
		return (NULL);
    ptr = ft_create_block(zone, type, size, len);
    if (!ptr)
        return (NULL);
    if (type != LARGE)
	    prepare_nzone(zone);
	g_zones_list = ft_addinlist(zone);
	return (ptr);
}