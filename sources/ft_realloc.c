/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 20:16:43 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/19 04:44:30 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*ft_realloc(void *ptr, size_t size, int force)
{
	void			*new_ptr;
	size_t			ptr_len;

	new_ptr = ft_malloc(size);
	if (!new_ptr)
	{
		if (force && ptr)
			ft_free(ptr);
		return (NULL);
	}
	if (ptr)
	{
		ptr_len = ft_block_len(ptr);
		if (ptr_len == 0)
			return (NULL);
		if (ptr_len > size)
			ptr_len = size;
		ft_memcpy(new_ptr, ptr, ptr_len);
		ft_free(ptr);
	}
	return (new_ptr);
}

void	*reallocf(void *ptr, size_t size)
{
	void	*new_ptr;

	new_ptr = ft_realloc(ptr, size, 1);
	return (new_ptr);
}

void	*realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	pthread_mutex_lock(&g_lock);
	new_ptr = ft_realloc(ptr, size, 0);
	pthread_mutex_unlock(&g_lock);
	return (new_ptr);
}
