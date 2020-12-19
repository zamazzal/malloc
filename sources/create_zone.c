/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_zone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 20:14:38 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/19 04:44:01 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		*ft_mmap(size_t len)
{
	void			*ptr;

	if (len < 1)
		return (NULL);
	ptr = mmap(NULL, len
	, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	return (ptr);
}

static void		*ft_create_block(void *ptr, int type, size_t size, size_t len)
{
	t_zones		*new_zone;
	t_block		*new_block;
	void		*new_ptr;

	new_zone = (void*)ptr;
	new_zone->zone_type = type;
	new_zone->size = len;
	new_zone->next = NULL;
	new_block = (void*)new_zone + sizeof(t_zones);
	new_block->size = size;
	new_block->alc = IS_ALLOCATED;
	new_block->next = NULL;
	new_ptr = ptr + sizeof(t_block) + sizeof(t_zones);
	return (new_ptr);
}

void			*create_new_zone(size_t size, int type)
{
	size_t	len;
	void	*ptr;
	t_zones	*zone;

	len = ft_getlen(type, size);
	zone = (t_zones*)ft_mmap(len);
	if (!zone)
		return (NULL);
	ptr = ft_create_block(zone, type, size, len);
	if (!ptr)
		return (NULL);
	g_zones_list = ft_addinlist(zone);
	return (ptr);
}
