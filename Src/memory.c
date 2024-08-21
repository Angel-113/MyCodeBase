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

void* ArenaAlloc ( Arena* A, size_t size, Grow g ) {

    void* ptr = NULL;

    if ( A->offset + size > A->size ) {
        switch (g) {
            default:
                break;
            case STATIC:
                perror("This arena is not big enough");
                break;
            case DYNAMIC:
                A = ExtendArena(A);
                break;
        }
    }

    ptr = A->arena + A->offset;
    A->offset += size;

    return ptr;

}

Arena* ExtendArena ( Arena* arena ) { /* This function supposes that arena has reached its maximum capacity */
    if (arena->offset >= arena->size) {
        Arena* new_arena = CreateArena(2 * arena->size);
        char* start = arena->arena - arena->size;
        for (int i = 0; i < arena->size; i++) new_arena->arena[i] = start[i];
        new_arena->offset = arena->size;
        DestroyArena(arena);
        return new_arena;
    }
    return arena;
}

void DestroyArena ( Arena* A ) {
    free ( A->arena );
    A->offset = 0;
    A->size = 0;
    free ( A );
    A = NULL;
}