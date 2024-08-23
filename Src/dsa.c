//
// Created by angel on 19/08/24.
//

#include "dsa.h"
/* Node Implementations */
static void* InitNode ( void* node, void* data, Type t );
static void InitNodeInt ( NodeInt* node, int data );
static void InitNodeFloat ( NodeFloat* node, float data );
static void InitNodeDouble ( NodeDouble* node, double data );
static void InitNodeString ( NodeString* node, char* data );
static void InitNodeVar ( NodeVar* node, void* data );
static void PrintNode ( void* node, Type t );

static void* InitNode ( void* node, void* data, const Type t ) {
    switch (t) {
        default:break;
        case INT:
            InitNodeInt(node, *((int*)data));
        break;
        case FLOAT:
            InitNodeFloat(node, *((float*)data));
        break;
        case DOUBLE:
            InitNodeDouble(node, *((double*)data));
        break;
        case STRING:
            InitNodeString(node, (char*)data);
        break;
        case VAR:
            InitNodeVar(node, data);
        break;
    }
    return node;
}

static void InitNodeInt ( NodeInt* node, const int data ) {
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
}

static void InitNodeFloat ( NodeFloat* node, const float data ) {
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
}

static void InitNodeDouble ( NodeDouble* node, const double data ) {
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
}

static void InitNodeString ( NodeString* node, char* data ) {
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
}

static void InitNodeVar ( NodeVar* node, void* data ) {
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
}

static void PrintNode ( void* node, Type t ) {

}

/* Linked List Implementations */
LL* InitList ( void* data, const Type t ) {
    LL* list = malloc(sizeof(LL));

    list->memory_pool = CreateArena(10 * sizeof(NodeVar));
    list->head = ArenaAlloc(list->memory_pool, sizeof(NodeVar), DYNAMIC);
    list->head = InitNode(list->head, data, t);
    list->size += 1;
    list->type = t;

    const NodeVar* tmp = list->head;
    list->tail = tmp->next;

    return list;
}