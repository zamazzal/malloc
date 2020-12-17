/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 20:16:43 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/16 20:16:45 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*ft_realloc(void *ptr, size_t size)
{
	void			*new_ptr;
	struct rlimit	rlp;
	size_t			ptr_len;

	new_ptr = ft_malloc(size);
    if (!new_ptr)
        return (NULL);
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

void	*realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	new_ptr = ft_realloc(ptr, size);
	return (new_ptr);
}