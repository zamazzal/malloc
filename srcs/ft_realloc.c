/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 11:04:26 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/16 19:46:57 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*ft_realloc(void *ptr, size_t size)
{
	void			*new_ptr;
	struct rlimit	rlp;
	size_t			ptr_len;

	if (getrlimit(RLIMIT_MEMLOCK, &rlp) == -1)
		return (NULL);
	if (rlp.rlim_cur < size || size < 1)
		return (NULL);
	new_ptr = ft_malloc(size);
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
