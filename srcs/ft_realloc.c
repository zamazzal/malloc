/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 11:04:26 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/15 11:04:29 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*ft_realloc(void *ptr, size_t size)
{
	void			*new_ptr;
	struct rlimit	rlp;
	void			*ptr_backup;
	size_t			ptr_len;

	if (getrlimit(RLIMIT_MEMLOCK, &rlp) == -1)
		return (NULL);
	if (rlp.rlim_cur < size || size < 1)
		return (NULL);
	if (ptr != NULL)
	{
		ptr_len = ft_block_len(ptr);
		ptr_backup = ft_malloc(ptr_len);
		ft_memcpy(ptr_backup, ptr, ptr_len);
	}
	ft_free(ptr);
	new_ptr = ft_malloc(size);
	if (ptr != NULL)
	{
		ft_memcpy(new_ptr, ptr_backup, size);
		ft_free(ptr_backup);
	}
	return (new_ptr);
}
