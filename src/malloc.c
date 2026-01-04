#include "memory_manager.h"
// #include

t_zones g_zones = {NULL};

bool initZones()
{
    g_zones.tiny = (t_memHeader *)mmap(NULL, TINYSIZE, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
    g_zones.small = (t_memHeader *)mmap(NULL, SMALLSIZE, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
    
    if (!g_zones.tiny || !g_zones.small)//checking mmap error
        return 0;

    /////////init first tiny zone///////////////
    g_zones.tiny->userMemory = (char *)g_zones.tiny + sizeof(t_memHeader);// g_zone.tiny + x ajoute x element de taille g_zone.tiny et g_zone + 1 trompe le compilateur qui pense qu'il s'agit d'un tableau
    g_zones.tiny->zoneStart = g_zones.tiny;
    g_zones.tiny->zoneEnd = (char *)g_zones.tiny + TINYSIZE;
    g_zones.tiny->size = TINYSIZE - sizeof(t_memHeader);
    g_zones.tiny->zoneLenght = TINYSIZE;
    g_zones.tiny->isFree = YES;
    g_zones.tiny->next = NULL;
    g_zones.tiny->prev = NULL;
    
    /////////init first small zone//////////////
    g_zones.small->userMemory = (char *)g_zones.small + sizeof(t_memHeader);
    g_zones.small->zoneStart = g_zones.small;
    g_zones.small->zoneEnd = (char *)g_zones.small + SMALLSIZE;
    g_zones.small->size = SMALLSIZE - sizeof(t_memHeader);
    g_zones.small->zoneLenght = SMALLSIZE;
    g_zones.small->isFree = YES;
    g_zones.small->next = NULL;
    g_zones.small->prev = NULL;

    return 1;
}

void *createNewZone(size_t size)//create newZone and fill it, doesn't fill "prev" thought
{
    t_memHeader *newZone = (t_memHeader *)mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
    if (!newZone)
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
    //reach an available freememHeader
    // printf("parser->size :%ld\n", parser->size);
    while(parser->isFree == NO || parser->size < alignedUserSize)//tant que on a pas de block assez grand pour stocker size
    {
        // printf("parser->size :%ld\n", parser->size);
        if (parser->next == NULL && (char *)parser->zoneEnd - ((char *)parser->userMemory + parser->size) > (long int)alignedBlockSize)//si on dépasse une zone/qu'il n'y en a plus
        {   //printf("creating new zone\n");
            parser->next = createNewZone(zoneSize);//ATTENTION get the good size, in arg i think
            if (!parser->next)
                return NULL;
            parser->next->prev = parser;
        }
        parser = parser->next;
    }
    //useable place found
    // parser->size = alignedUserSize; //uniquelent si on optimise avec "coupe"
    parser->isFree = NO;
    parser->userMemory = (char *)parser + sizeof(t_memHeader);
    // printf("found useable place for %ld size\n", parser->size);

    if (!parser->next)//pas besoins de "couper" la zone valide. On ne coupe que si on veux optimiser
    {//si on est la, on était sur la fin de la chaine
        size_t memLeft = (size_t)((char *)parser->zoneEnd - (char *)parser->next - sizeof(t_memHeader));
        
        parser->size = alignedUserSize;//a enlever si on "coupe"

        if(memLeft < sizeof(t_memHeader))//pas la place d'un header avant fin de zone
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
        }
        parser->next->prev = parser;
    
    }
    return parser->userMemory;
}

void *largeAlloc(size_t alignedUserSize, size_t alignedBlockSize)
{
    t_memHeader *newBlock = mmap(NULL, alignedBlockSize, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
    t_memHeader *largeList = g_zones.large;
    
    if (!newBlock)
        return NULL;

    newBlock->isFree = NO;
    newBlock->next = NULL;
    newBlock->size = alignedUserSize;
    newBlock->userMemory = (char *)newBlock + sizeof(t_memHeader);
    newBlock->zoneEnd = NULL; //not important
    if (!largeList)
        g_zones.large = newBlock;
    else
    {
        while(largeList->next)
            largeList = largeList->next;
        largeList->next = newBlock;
    }
    return newBlock->userMemory;
        
}


void *malloc(size_t size)//alliner size sur la memoire physique (8 ou 16)
{
    if (size <= 0)
        return NULL;
    // if (g_zones.tiny == 0)//first call
    // {
    //     if (!initZones())
    //         return NULL;
    // }
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

