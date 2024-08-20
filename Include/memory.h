//
// Created by angel on 19/08/24.
//

#ifndef MYCODEBASE_MEMORY_H
#define MYCODEBASE_MEMORY_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Arena {
    char* arena;
    size_t size;
    size_t offset;
} Arena;

extern Arena* CreateArena ( size_t size );
extern void ExtendArena ( Arena* arena );
extern void* ArenaAlloc ( Arena* A, size_t size );
extern void DestroyArena ( Arena* A );

#endif //MYCODEBASE_MEMORY_H
