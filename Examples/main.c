//
// Created by angel on 19/08/24.
//

#include <stdio.h>
#include "memory.h"
#include "dsa.h"
#include "utilities.h"

int main ( void ) {
    Arena* memory_pool = CreateArena( 2 * sizeof(char) );
    printf("Memory pool dir  = %p, Memory size and offset = { %zu, %zu }\n", memory_pool->arena, memory_pool->size, memory_pool->offset );
    memory_pool = ExtendArena(memory_pool, 2 * memory_pool->size);
    printf("Memory pool dir  = %p, Memory size and offset = { %zu, %zu }\n", memory_pool->arena, memory_pool->size, memory_pool->offset );
    DestroyArena(memory_pool);
    return 0;
}
