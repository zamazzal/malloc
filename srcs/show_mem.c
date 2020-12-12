
#include "malloc.h"

static void    ft_show_zone(t_zones *zone)
{
    if (zone->zone_type == 1)
        printf("%s : ", "TINY");
    else if (zone->zone_type == 2)
        printf("%s : ", "SMALL");
    else
        printf("%s : ", "LARGE");
    printf("%p\n", zone);
}

static void    ft_show_block(void *ptr, size_t len)
{
    static size_t total = 0;

    total += len;

    printf("%p - %p: %ld bytes\n", ptr, ptr + len, len);
}

static size_t  show_block_mem(void *ptr, size_t *x)
{
    t_block *block_ptr;

    block_ptr = ptr + *x;
    if (block_ptr && block_ptr->size >= 1)
    {
        //printf("find : %zu\n", *x);
        *x = *x + sizeof(t_block) + block_ptr->size;
        if (block_ptr->alc == IS_ALLOCATED) // delete this after the testes
        {
            ft_show_block(block_ptr + sizeof(t_block), block_ptr->size);
            return (block_ptr->size);
        }
    }
    else
    {
        //printf("not found : %zu\n", *x);
        (*x)++;
    }
    return (0);
}

void     show_alloc_mem()
{
    t_zones *tmp;
    size_t x;
    size_t rzlt;
    static size_t total = 0;

    tmp = g_zones_list;
    while (tmp != NULL)
    {
        ft_show_zone(tmp);
        x = sizeof(t_zones);
        while (x - 1 < tmp->size)
        {
            rzlt = show_block_mem(tmp, &x);
            total += rzlt;
            if (rzlt && tmp->zone_type == LARGE)
                break ;
        }
        tmp = tmp->next;
    }
    printf("Total : %zu bytes\n", total);
}