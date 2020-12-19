/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 20:13:06 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/19 04:45:30 by zamazzal         ###   ########.fr       */
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
	malloc_log(ptr, new_z);
	return (ptr);
}

void			*ft_malloc(size_t size)
{
	void			*ptr;

	if (size < 1)
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

void			*calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	m_size;

	pthread_mutex_lock(&g_lock);
	m_size = size * nmemb;
	if (nmemb <= 0 || size <= 0 || m_size <= 0)
		return (NULL);
	if (m_size / size != nmemb)
		return (NULL);
	ptr = ft_malloc(m_size);
	ft_bzero(ptr, m_size);
	pthread_mutex_unlock(&g_lock);
	return (ptr);
}
