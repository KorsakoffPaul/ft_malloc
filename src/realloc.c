#include "memory_manager.h"

void *realloc(void *ptr, size_t size)
{
    if(!ptr)
        return malloc(size);
    if(size == 0)
    {
        free(ptr);
        return NULL;
    }
    
    if(!inZones(ptr))//|| inzone(ptr - headerSize)
        return NULL;//ptr is either NULL or not in range of my program
    t_memHeader *blockToRealloc = (t_memHeader *)((char *)ptr - sizeof(t_memHeader));
    if(blockToRealloc->userMemory != ptr)//ptr must be headersize after my zones starts
        return NULL;//ptr is not pointing an adress returned by malloc

    if(blockToRealloc->size >= size)//tant qu'on optimise pas la "coupe" coté malloc
        return blockToRealloc->userMemory;

    if (blockToRealloc->next && blockToRealloc->next->isFree && blockToRealloc->size + blockToRealloc->next->size >= size)
    {
        merge(blockToRealloc, blockToRealloc->next);
        return blockToRealloc->userMemory;
    }

    void *newPlace = malloc(size);
    if(!newPlace)
        return NULL;
    ft_memcpy(newPlace, blockToRealloc->userMemory, blockToRealloc->size < size ? blockToRealloc->size : size);
    free(blockToRealloc->userMemory);
    return newPlace;
}