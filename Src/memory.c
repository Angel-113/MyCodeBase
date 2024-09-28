//
// Created by angel on 19/08/24.
//

#include "memory.h"

Arena* CreateArena ( const size_t size ) {
    Arena* arena = safe_malloc(sizeof(Arena));
    arena->arena = (byte *) safe_malloc(size);
    arena->size = size;
    arena->offset = 0;
    return arena;
}

void* ArenaAlloc ( Arena* arena, const size_t size, Grow g) {
    void *ptr = NULL;

    if (arena->offset + size > arena->size && size != 0) {
        switch (g) {
            default:
                break;
            case STATIC:
                log_error("This arena is not big enough !!! ");
                return ptr;
            case DYNAMIC:
                ExtendArena(arena, 2 * size);
            break;
        }
    }

    ptr = arena->arena + arena->offset;
    arena->offset += size;
    arena->size += (size_t) (size / sizeof(byte));

    return ptr;
}

void ExtendArena ( Arena* arena, const size_t size ) {
    arena->arena = (byte*) safe_realloc(arena->arena, (arena->size + size) * sizeof(byte));
    arena->size += size;
}

void DestroyArena ( Arena* arena ) {
    safe_free ( arena->arena );
    arena->offset = 0;
    arena->size = 0;
    safe_free ( arena );
    arena = NULL;
}