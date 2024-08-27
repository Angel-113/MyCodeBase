//
// Created by angel on 19/08/24.
//

#include "dsa.h"

static Arena *memory_pool = NULL;

static size_t NodeSize ( Type t );
static void AuxInitNode ( void* data, void* node, Type t );
static void PrintNode ( void* node, Type t );

void dsa_init ( void ) { memory_pool = memory_pool == NULL ? CreateArena(512) : memory_pool; }

void dsa_close ( void ) { DestroyArena(memory_pool); }

void PrintList ( void* head, const Type t ) {
    NodeVar* tmp = head;
    while ( (void*)tmp != NULL ) {
        void* tmp1 = tmp;
        PrintNode(tmp1, t);
        tmp = tmp->next;
    }
}

void* NodeInit ( void* data, const Type t ) {
    void* ptr = NULL;
    ptr = ArenaAlloc(memory_pool, NodeSize(t), DYNAMIC);
    AuxInitNode(data, ptr, t);
    return ptr;
}

static size_t NodeSize ( const Type t ) {
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

static void AuxInitNode ( void* data, void* node, const Type t ) {
    switch (t) {
        default:
            break;
        case INT:
            NodeInt* node1 = (NodeInt *) node;
            node1->data = *(int*)data;
            node1->prev = node1->next = NULL;
        break;
        case FLOAT:
            NodeFloat* node2 = (NodeFloat *) node;
            node2->data = *(float*)data;
            node2->prev = node2->next = NULL;
        break;
        case DOUBLE:
            NodeDouble* node3 = (NodeDouble *) node;
            node3->data = *(double*)data;
            node3->prev = node3->next = NULL;
        break;
        case STRING:
            NodeString* node4 = (NodeString *) node;
            node4->data = (char *)data;
            node4->prev = node4->next = NULL;
        break;
        case VAR:
            NodeVar* node5 = (NodeVar *) node;
            node5->data = data;
            node5->prev = node5->next = NULL;
        break;
    }
}

static void PrintNode ( void* node, const Type t ) {
    if (node == NULL) {
        printf("{ NULL }\n");
        return;
    }
    switch (t) {
        default:
            break;
        case INT:
            const NodeInt* node1 = (NodeInt *) node;
            printf(" <---- { %p, %d, %p } ----> ", node1->prev, node1->data, node1->next);
            break;
        case FLOAT:
            const NodeFloat* node2 = (NodeFloat *) node;
            printf(" <---- { %p, %f, %p } ----> ", node2->prev, node2->data, node2->next);
            break;
        case DOUBLE:
            const NodeDouble* node3 = (NodeDouble *) node;
            printf(" <---- { %p, %f, %p } ----> ", node3->prev, node3->data, node3->next);
            break;
        case STRING:
            const NodeString* node4 = (NodeString *) node;
            printf(" <---- { %p, '%s', %p } ----> ", node4->prev, node4->data, node4->next);
            break;
        case VAR:
            const NodeVar* node5 = (NodeVar *) node;
            printf(" <---- { %p, %p, %p } ----> ", node5->prev, node5->data, node5->next);
            break;
    }
}