/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 20:16:43 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/16 20:16:45 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*malloc(size_t size)
{
	void	*ptr;

	ptr = ft_malloc(size);
	return (ptr);
}

void	*realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	new_ptr = ft_realloc(ptr, size);
	return (new_ptr);
}

void	free(void *ptr)
{
	ft_free(ptr);
}