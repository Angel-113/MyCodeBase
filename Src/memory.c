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

void* ArenaAlloc ( Arena* A, size_t size ) {
    if ( A->offset + size > A->size ) {
        perror("This arena is not big enough");
        return NULL;
    }
    void* ptr = A->arena + A->offset;
    A->offset += size;
    return ptr;
}

void ExtendArena ( Arena* arena ) { /* This function supposes that arena has reached its maximum capacity */

    /* Still thinking in how to extend an arena */

}

void DestroyArena ( Arena* A ) {
    free ( A->arena );
    A->offset = 0;
    A->size = 0;
    free ( A );
    A = NULL;
}