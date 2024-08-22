//
// Created by angel on 19/08/24.
//

#include "memory.h"

Arena* CreateArena ( size_t size ) {
    Arena* arena = (Arena*) malloc(sizeof(Arena));
    if ( arena != NULL ) {
        arena->arena = (char *) malloc(size);
        if ( arena->arena == NULL ) {
            perror("Error when creating Arena\n");
            return NULL;
        }
        arena->size = size;
        arena->offset = 0;
    }
    return arena;
}

void* ArenaAlloc ( Arena* A, size_t size) {
    void* ptr = NULL;
    if ( A->offset + size > A->size ) perror("\nThis arena is not big enough !!! \nTry creating another one with greater size");
    else {
        ptr = A->arena + A->offset;
        A->offset += size;
    }

    return ptr;
}

Arena* ExtendArena ( Arena* arena ) { /* This function supposes that arena has reached its maximum capacity */
    /*
     * I was just thinking in create another arena and to copy all the bits from the first one
     * to the new one. Then destroy the first one and return the new one. It seems to be a problem cause
     * memory is leaked. I'll take some time on dev a safe way to grow an arena.
     */
    return NULL;
}

void DestroyArena ( Arena* A ) {
    free ( A->arena );
    A->offset = 0;
    A->size = 0;
    free ( A );
    A = NULL;
}