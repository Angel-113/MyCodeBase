//
// Created by angel on 19/08/24.
//

#ifndef MYCODEBASE_MEMORY_H
#define MYCODEBASE_MEMORY_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef enum Grow {
    DYNAMIC = 1,
    STATIC = 0
} Grow;

typedef struct Arena {
    char* arena;
    size_t size;
    size_t offset;
} Arena;

extern Arena* CreateArena ( size_t size );
extern Arena* ExtendArena ( Arena* arena, size_t size /* size is the last's allocation trial size */ );
extern void* ArenaAlloc ( Arena* A, size_t size);
extern void DestroyArena ( Arena* A ); /* Maybe should do something else */

#endif //MYCODEBASE_MEMORY_H
