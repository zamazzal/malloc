/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 20:13:06 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/21 18:22:55 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		*alloc_by_type(size_t size)
{
	int		type;
	void	*ptr;
	int		new_z;

	ptr = NULL;
	new_z = 0;
	type = ft_check_type(size);
	if (type != LARGE)
		ptr = create_in_existing_z(size, type);
	if (ptr == NULL)
	{
		ptr = create_new_zone(size, type);
		new_z = 1;
	}
	if (ptr && (DEBUG || LOG))
		malloc_log(ptr, size);
	return (ptr);
}

void			*ft_malloc(size_t size)
{
	void			*ptr;

	if (!size)
		return (NULL);
	ptr = alloc_by_type(size);
	return (ptr);
}

void			*malloc(size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&g_lock);
	ptr = ft_malloc(size);
	pthread_mutex_unlock(&g_lock);
	return (ptr);
}

void			*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	m_size;

	pthread_mutex_lock(&g_lock);
	if (!nmemb || !size)
		return (NULL);
	m_size = size * nmemb;
	if (m_size <= 0 || m_size / size != nmemb)
		return (NULL);
	ptr = ft_malloc(m_size);
	if (ptr)
		ft_bzero(ptr, m_size);
	pthread_mutex_unlock(&g_lock);
	return (ptr);
}
