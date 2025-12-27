#include "memory_manager.h"

/*assoccie la zone first et second, étant l'ordre dans le memoire physique
**gère si les deux arguments sont dans la meme zone
*/
void merge(t_memHeader *firstBlock, t_memHeader *secondBlock)
{
    if (firstBlock->zoneStart != secondBlock->zoneStart)//si de la meme zone
        return;
    firstBlock->next = secondBlock->next;
    firstBlock->size = firstBlock->size + secondBlock->size + sizeof(t_memHeader);
    if (secondBlock->next)
        secondBlock->next->prev = firstBlock;

}

bool searchInZone(uintptr_t ptr, t_memHeader *parser)
{
    while(parser)
    {
        if ((uintptr_t)parser->zoneStart <= ptr && (uintptr_t)parser->zoneEnd > ptr)
            return 1;
       parser = parser->next;
    }
    return 0;
}

bool inZones(void *ptr)
{
    bool validPtr = NO;
    uintptr_t intptr = (uintptr_t)ptr;

    validPtr = searchInZone(intptr, g_zones.tiny);
    if (!validPtr)
        validPtr = searchInZone(intptr, g_zones.small);
    if (!validPtr)
        validPtr = searchInZone(intptr, g_zones.large);

    return validPtr;
}

void free(void *ptr)
{
    // (void)ptr;
    if(!ptr || !inZones(ptr))
        return ;//ptr is either NULL or not in range of my program
    t_memHeader *blockToFree = (t_memHeader *)((char *)ptr - sizeof(t_memHeader));
    if(blockToFree->userMemory != ptr)
        return ;//ptr is not pointing an adress returned by malloc
    if (blockToFree->isFree == YES)
        return ;//double free
    blockToFree->isFree = YES;

    if(blockToFree->next && blockToFree->next->isFree == YES)
        merge(blockToFree, blockToFree->next);
    if(blockToFree->prev && blockToFree->prev->isFree == YES)
        merge(blockToFree->prev, blockToFree);
}