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

void* ArenaAlloc ( Arena* arena, const size_t size, Grow g) {
    void *ptr = NULL;

    if (arena->offset + size > arena->size) {
        switch (g) {
            default:
                break;
            case STATIC:
                printf("\nThis arena is not big enough!!!\n");
                return ptr;
            case DYNAMIC:
                arena = ExtendArena(arena, 2 * (size - arena->size < 0 ? -1*(size - arena->size) : size - arena->size));
                break;
        }
    }

    ptr = arena->arena + arena->offset;
    arena->offset += size;

    return ptr;
}

Arena* ExtendArena ( Arena* arena, const size_t size ) {
    arena->arena = (char*)realloc(arena->arena, (arena->size + size) * sizeof(char));
    arena->size += size;
    return arena;
}

void DestroyArena ( Arena* A ) {
    free ( A->arena );
    A->offset = 0;
    A->size = 0;
    free ( A );
    A = NULL;
}