#include "memory_manager.h"

t_zones g_zones = {0};

void *createNewZone(size_t size)//create newZone and fill it, doesn't fill "prev" thought
{
    t_memHeader *newZone = (t_memHeader *)mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
    if (newZone == MAP_FAILED)
        return NULL;
    newZone->zoneLenght = size;
    newZone->isFree = YES;
    newZone->next = NULL;
    newZone->prev = NULL;
    newZone->size = size - sizeof(t_memHeader);
    newZone->userMemory = (char *)newZone + sizeof(t_memHeader);
    newZone->zoneStart = newZone;
    newZone->zoneEnd = (char *)newZone + size;

    return newZone;
}

void *tinySmallAlloc(t_memHeader *parser, size_t alignedUserSize, size_t alignedBlockSize, size_t zoneSize)//ici size = alignedUserSize + alligneHeaderSiez
{
    if (!parser)
    {
        parser = createNewZone(zoneSize);
        if (!parser)
            return NULL;
        if (zoneSize == TINYSIZE)
            g_zones.tiny = parser;
        else
            g_zones.small = parser;
    }


    while(parser->isFree == NO || parser->size < alignedUserSize)//while no block arge enought to fit usersize
    {
        if (parser->next == NULL && (char *)parser->zoneEnd - ((char *)parser->userMemory + parser->size) > (long int)alignedBlockSize)//si on dépasse une zone/qu'il n'y en a plus
        {
            parser->next = createNewZone(zoneSize);
            if (!parser->next)
                return NULL;
            parser->next->prev = parser;
        }
        parser = parser->next;
    }

    parser->isFree = NO;
    parser->userMemory = (char *)parser + sizeof(t_memHeader);

    if (!parser->next)//here we are at the end of list
    {	
        int memLeft = (int)((char *)parser->zoneEnd - (char *)parser - alignedBlockSize - sizeof(t_memHeader));
        parser->size = alignedUserSize;
        if(memLeft < (int)sizeof(t_memHeader))//no place for another header before next zone
        {
            parser->next = createNewZone(zoneSize);
            if (!parser->next)
                return NULL;
        }
        else
        {
            parser->next = (t_memHeader *)((char *) parser + alignedBlockSize);
            parser->next->isFree = YES;
            parser->next->size = memLeft;
            parser->next->zoneStart = parser->zoneStart;
            parser->next->zoneEnd = parser->zoneEnd;
			parser->next->next = NULL;

        }
        parser->next->prev = parser;
    }
    return parser->userMemory;
}

void *largeAlloc(size_t alignedUserSize, size_t alignedBlockSize)
{
    t_memHeader *newBlock = mmap(NULL, alignedBlockSize, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
    t_memHeader *largeList = g_zones.large;
    
    if (newBlock == MAP_FAILED)
        return NULL;

    newBlock->zoneStart = (void *)newBlock;
    newBlock->isFree = NO;
    newBlock->next = NULL;
    newBlock->prev = NULL;
    newBlock->size = alignedUserSize;
    newBlock->userMemory = (char *)newBlock + sizeof(t_memHeader);
    newBlock->zoneEnd = (char *)newBlock + alignedBlockSize;
    if (!largeList)
        g_zones.large = newBlock;
    else
    {
        while(largeList->next)
            largeList = largeList->next;
        newBlock->prev = largeList;
        largeList->next = newBlock;
    }
    return newBlock->userMemory;
        
}


void *malloc(size_t size)
{
    if (size <= 0)
        return NULL;

    size_t alignedUserSize = (size + ALIGNMENT - 1) & ~(ALIGNMENT - 1);//taille utilisateur alligné
    size_t alignedBlockSize = alignedUserSize + sizeof(t_memHeader);//taille utilisateur alligné + header alligné
    if (size <= 256)
        return(tinySmallAlloc(g_zones.tiny, alignedUserSize, alignedBlockSize, TINYSIZE));
    else if (size >= 4096)
        return(largeAlloc(alignedUserSize, alignedBlockSize));
    else
        return(tinySmallAlloc(g_zones.small, alignedUserSize, alignedBlockSize, SMALLSIZE));
    return NULL;//error
}

