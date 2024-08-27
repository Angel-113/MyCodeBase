//
// Created by angel on 19/08/24.
//

#include "dsa.h"

static Arena *memory_pool = NULL;

static size_t NodeSize(const Type t);
static void AuxInitNode ( void* data, void* node, Type t );

void dsa_init ( void ) { memory_pool = memory_pool == NULL ? CreateArena(512) : memory_pool; }
void dsa_close ( void ) { DestroyArena(memory_pool); }

DLL* DLLInit ( void* data, const Type t ) {
    if ( memory_pool == NULL ) {
        log_error("DSA not initialized");
        exit(EXIT_FAILURE);
    }

    DLL* dll = ArenaAlloc(memory_pool, sizeof(DLL), DYNAMIC);
    dll->head = dll->tail = NodeInit(data,t );
    dll->size += 1;

    return dll;
}



void* NodeInit ( void* data, const Type t ) {
    void* ptr = NULL;
    ptr = ArenaAlloc(memory_pool, NodeSize(t), DYNAMIC);

    return ptr;
}

static size_t NodeSize(const Type t) {
    size_t size = 0;
    switch (t) {
        default:
            break;
        case INT:
            size = sizeof(NodeInt);
        break;
        case FLOAT:
            size = sizeof(NodeFloat);
        break;
        case STRING:
            size = sizeof(NodeString);
        break;
        case DOUBLE:
            size = sizeof(NodeDouble);
        break;
        case VAR:
            size = sizeof(NodeVar);
        break;
    }
    return size;
}