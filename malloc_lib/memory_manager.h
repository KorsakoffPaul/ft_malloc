#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>


#define YES 1
#define NO 0
#define ALIGNMENT 16
#define TINYSIZE 32768
#define SMALLSIZE 106496

typedef struct s_memHeader
{
    void *zoneEnd;
    void *userMemory;
    size_t size;
    bool isFree;
    struct s_memHeader *next;
    char pading[8];
}t_memHeader __attribute__((aligned(ALIGNMENT)));


typedef struct s_zones
{
    t_memHeader *tiny;
    t_memHeader *small;
    t_memHeader *large;

}t_zones;

extern t_zones g_zones;

void show_alloc_mem();


#endif