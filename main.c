#include "malloc.h"
size_t  multipleof_pages(size_t size)
{
    size_t page_size;
    page_size = getpagesize();
    while (size % page_size != 0)
        size++;
    return (size);
}
int ft_check_type(size_t size)
{
    if (size > SMALL_SIZE)
        return (LARGE);
    else if (size > TINY_SIZE)
        return (SMALL);
    else
        return (TINY);
}
// check this

void    *ft_reserv_zone(t_block *block, size_t size) // t5wira
{
    t_block *next_b;
    size_t x;

    if (block->size == size)
    {
        block->alc = IS_ALLOCATED;
        block->size = size;
        return (block + sizeof(t_block));
    }
    else if (block->size > size)
    {
        x = (block->size - sizeof(t_block) - size);
        if (x < 1)
        {
            block->alc = IS_ALLOCATED;
            block->size = block->size;
            return (block + sizeof(t_block));
        }
        next_b = (void*)block + sizeof(t_block) + size;
        next_b->alc = 0;
        next_b->size = x;
        block->alc = IS_ALLOCATED;
        block->size = size;
        return (block + sizeof(t_block));
    }
    return (NULL);
}

void *ft_getblock(t_zones *list, size_t size)
{
    size_t x;
    t_block *block;
    void *ptr;

    ptr = NULL;
    x = sizeof(t_zones);
    while (x - 1 < list->size)
    {
        block = (void*)list + x;
        if (block && block->size >= 1)
        {
            x += sizeof(t_block) + block->size;
            if (!block->alc)
            {
                printf("--------> 1 %zu\n", block->size);
                if ((ptr = ft_reserv_zone(block, size)))
                    return (ptr);
            }
        }
        else
            x++;
    }
    return (NULL);
}

void *create_in_existing_z(size_t size, int type)
{
    t_zones *tmp;
    void *ptr;

    tmp = g_zones_list;
    while (tmp != NULL)
    {
        if (tmp->zone_type == type)
        {
            printf("found list\n");
            ptr = ft_getblock(tmp, size);
            if (ptr != NULL)
                return (ptr);
        }
        tmp = tmp->next;
    }
    return (NULL);
}

size_t get_size_bytype(int type)
{
    size_t size;

    if (type == TINY)
        size = TINY_SIZE;
    if (type == SMALL)
        size = SMALL_SIZE;
    return (size);
}
size_t ft_getlen(int type)
{
    size_t len;
    size_t len_by_type;

    len_by_type = get_size_bytype(type);
    len = (len_by_type + sizeof(t_block)) * PREALLOC_SIZE;
    len += sizeof(t_zones);
    len = multipleof_pages(len);
    return (len);
}
t_zones *ft_addinlist(t_zones *new_zone)
{
    t_zones *tmp;

    if (g_zones_list == NULL)
        return (new_zone);
    tmp = g_zones_list;
    while (g_zones_list->next != NULL)
        g_zones_list = g_zones_list->next;
    g_zones_list->next = new_zone;
    g_zones_list = tmp;
    return (g_zones_list);
}
void *create_new_zone(size_t size, int type)
{
    void *ptr;
    size_t len;
    t_zones *new_zone;
    t_block *new_block;

    len = ft_getlen(type);

    new_zone = mmap(NULL, len
    , PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, 0, 0);
    if(new_zone == MAP_FAILED)
        return (NULL);
    bzero(new_zone, len);
    new_zone->zone_type = type;
    new_zone->size = len;
    new_zone->next = NULL;
    new_block = (void*)new_zone + sizeof(t_zones);
    new_block->size = size;
    new_block->alc = IS_ALLOCATED;


    size_t x = 0;
    t_block *new_block2;

    x = sizeof(t_zones) + sizeof(t_block) + size;
    while (x + 1 < len)
    {
        new_block2 = (void*)new_zone + x;
        new_block2->size = get_size_bytype(type);
        new_block2->alc = 0;
        x += sizeof(t_block) + get_size_bytype(type);
    }
    g_zones_list = ft_addinlist(new_zone);
    return (new_block + sizeof(t_block));
}
void *alloc_large_zone(size_t size)
{
    void *ptr;
    size_t len;
    t_zones *new_zone;
    t_block *new_block;

    len = multipleof_pages(size);
    new_zone = mmap(NULL, len
    , PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, 0, 0);
    if(new_zone == MAP_FAILED)
        return (NULL);
    bzero(new_zone, len);
    new_zone->zone_type = LARGE;
    new_zone->size = len;
    new_zone->next = NULL;
    new_block = (void*)new_zone + sizeof(t_zones);
    new_block->size = size;
    new_block->alc = IS_ALLOCATED;
    g_zones_list = ft_addinlist(new_zone);
    return (new_block + sizeof(t_block));
}
void *alloc_by_type(size_t size)
{
    int type;
    void *ptr;

    ptr = NULL;
    type = ft_check_type(size);
    if (type == TINY || type == SMALL)
    {
       if (!(ptr = create_in_existing_z(size, type)))
            ptr = create_new_zone(size, type);
    }
    else
        ptr = alloc_large_zone(size);
    return (ptr);
}
void *ft_malloc(size_t size)
{
    void *ptr;

    ptr = alloc_by_type(size);
    return (ptr);
}
///////////// show data

////////
int main(void)
{
    char *str;
    int len;
    str = ft_malloc(478);
    printf("-------------------------\n");
    str = ft_malloc(20);
    str = ft_malloc(478);
    str = ft_malloc(18);
    str = ft_malloc(478);
    str = ft_malloc(17);
    str = ft_malloc(478);
    str = ft_malloc(14);
    //str = memset(str, 'z', 5000);
    show_alloc_mem();
    return (0);
}