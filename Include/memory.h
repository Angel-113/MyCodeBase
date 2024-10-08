//
// Created by angel on 19/08/24.
//

#ifndef MYCODEBASE_MEMORY_H
#define MYCODEBASE_MEMORY_H

#define MAX_HEAP_SIZE 64000
#define MIN_HEAP_SIZE 8000

#include "base.h"
#include <sys/mman.h> /* for heap-like allocator */
#include <unistd.h> /* for simple allocator */

/*
 * TODO: Angel Castillo
 * FIXME: Make a non-linear allocator to push and could manage freeing memory.
*/

typedef enum Grow {
    DYNAMIC = 1,
    STATIC = 0
} Grow;

typedef struct Arena {
    byte* arena;
    size_t size;
    size_t offset;
} Arena;

extern Arena* CreateArena ( size_t size ); /* Creates an Arena struct ptr which has a byte* arena of size 'size' */
extern void ExtendArena ( Arena* arena, size_t size); /* This functions re-allocate arena->arena ptr to a ptr with double size */
extern void* ArenaAlloc ( Arena* arena, size_t size, Grow g); /* Allocate size bits and return a ptr to arena->arena + arena->offset */
extern void DestroyArena ( Arena* arena ); /* Frees arena struct ptr and arena->arena */

#endif //MYCODEBASE_MEMORY_H
