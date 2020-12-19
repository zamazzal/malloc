/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 16:18:09 by zamazzal          #+#    #+#             */
/*   Updated: 2020/12/19 04:59:00 by zamazzal         ###   ########.fr       */
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
# include <pthread.h>
# include <time.h>
# include <fcntl.h>

# define TINY 1
# define SMALL 2
# define LARGE 3
# define IS_ALLOCATED 1337

# define SMALL_SIZE 1024
# define TINY_SIZE 128
# define PREALLOC_SIZE 128

# define LOG_FILE "/var/tmp/malloc.log"

typedef struct		s_block
{
	size_t			size;
	int				alc;
	struct s_block	*next;
}					t_block;

typedef struct		s_zones
{
	int				zone_type;
	size_t			size;
	struct s_zones	*next;
}					t_zones;

t_zones				*g_zones_list;
pthread_mutex_t		g_lock;

void				*malloc(size_t size);
void				free(void *ptr);
void				*realloc(void *ptr, size_t size);
void				*calloc(size_t nmemb, size_t size);
void				*reallocf(void *ptr, size_t size);
void				show_alloc_mem(void);
void				show_alloc_mem_ex(void);

void				*create_in_existing_z(size_t size, int type);
void				*create_new_zone(size_t size, int type);

t_block				*ft_get_block(void *ptr);
t_zones				*ft_get_zone(void *ptr);
size_t				ft_blocks_info(void const *ptr);
size_t				ft_block_len(void const *ptr);

void				ft_free(void *ptr);
void				*ft_malloc(size_t size);
void				*ft_realloc(void *ptr, size_t size, int force);

t_zones				*ft_addinlist(t_zones *new_zone);
t_zones				*ft_delete_zone_list(t_zones *zone);

int					ft_check_type(size_t size);
size_t				get_size_bytype(int type);
size_t				multipleof_pages(size_t size);
size_t				ft_getlen(int type, size_t size);
int					check_zone_type_i(int type);

void				ft_show_zone(t_zones *zone);
size_t				ft_zone_info(void const *ptr);

void				malloc_log(void *ptr, int new_z);
void				free_log(void *ptr);
void				ft_print_time(int fd);
#endif
