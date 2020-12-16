/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 16:18:09 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/16 19:47:24 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <strings.h>
# include <sys/mman.h>
# include <unistd.h>
# include <time.h>
# define TINY 1
# define SMALL 2
# define LARGE 3
# define IS_ALLOCATED 1337

# define SMALL_SIZE 1024
# define TINY_SIZE 128
# define PREALLOC_SIZE 128

typedef struct		s_block
{
	size_t	size;
	int		alc;
}					t_block;

typedef struct		s_zones
{
	int				zone_type;
	size_t			size;
	struct s_zones	*next;
}					t_zones;

t_zones				*g_zones_list;

void				show_alloc_mem();
size_t				multipleof_pages(size_t size);
size_t				get_size_bytype(int type);
size_t				ft_getlen(int type);
int					ft_check_type(size_t size);
void				*alloc_large_zone(size_t size);
void				*create_in_existing_z(size_t size, int type);

void				*create_new_zone(size_t size, int type);

void				*ft_malloc(size_t size);
size_t				ft_blocks_info(void const *ptr);
void				ft_free(void *ptr);
void				*ft_realloc(void *ptr, size_t size);
size_t				ft_block_len(void const *ptr);
void				malloc_log(void *ptr, int new_z);
int					check_zone_type_i(int type);
int					ft_empty_zone(void);
#endif
