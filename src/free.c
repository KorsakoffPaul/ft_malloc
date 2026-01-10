#include "memory_manager.h"

/*assoccie la zone first et second, étant l'ordre dans le memoire physique
**gère si les deux arguments sont dans la meme zone
*/
void merge(t_memHeader *firstBlock, t_memHeader *secondBlock)//make a merge large
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
    if (!parser)
        return 0;
    while(parser)
    {
        if ((uintptr_t)parser->zoneStart <= ptr && (uintptr_t)parser->zoneEnd > ptr)//ICICICICICICICI
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

bool canMunmap(t_memHeader *parser)
{
    bool everythingFree = YES;
    void *zoneStart = parser->zoneStart;

    while(parser && everythingFree == YES)
    {
        if (parser->zoneStart != zoneStart)
            break;
        if(parser->isFree == NO)
            everythingFree = NO;
        parser = parser->next;
    }
    return everythingFree;
}

void prepareMunmap(t_memHeader *targetZone)
{
    t_memHeader *parser = targetZone;
    t_memHeader *prevZone = targetZone->prev;
    t_memHeader *nextZone;

    while(parser)
    {
        if (parser->zoneStart != targetZone->zoneStart)
            break;
        parser = parser->next;
    }
    nextZone = parser;

    if(!prevZone && !nextZone)
    {
        if(targetZone->zoneLenght == TINYSIZE)
            g_zones.tiny = NULL;
    }

    if(prevZone)
        prevZone->next = nextZone;
    if(nextZone)
        nextZone->prev = prevZone;
}

void free(void *ptr)//add ummap when zone empty
{
    if(!ptr || !inZones(ptr) || !inZones((char*)ptr - sizeof(t_memHeader)))
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
    if(canMunmap((t_memHeader *)blockToFree->zoneStart))
    {
        prepareMunmap((t_memHeader *)blockToFree->zoneStart);
        munmap(blockToFree->zoneStart, blockToFree->zoneLenght);
    }
}