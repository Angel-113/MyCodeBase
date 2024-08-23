//
// Created by angel on 19/08/24.
//

#ifndef MYCODEBASE_DSA_H
#define MYCODEBASE_DSA_H

#include "memory.h"

typedef enum Type {
    INT = 0,
    FLOAT = 1,
    DOUBLE = 2,
    STRING = 3,
    VAR = 4 /* a void* not recommendable if you're not allocating structures in the node */
} Type;

/*
 * It's better to create from scratch an LLStruct with a struct data you want to use
 * instead of using the LLVar. That's often better for memory and execution performance.
 */

typedef struct NodeInt {
    struct NodeInt* prev;
    int data;
    struct NodeInt* next;
} NodeInt;

typedef struct NodeFloat {
    struct NodeFloat* prev;
    float data;
    struct NodeFloat* next;
} NodeFloat;

typedef struct NodeDouble {
    struct NodeDouble* prev;
    double data;
    struct NodeDouble* next;
} NodeDouble;

typedef struct NodeString {
    struct NodeString* prev;
    char* data;
    struct NodeString* next;
} NodeString;

typedef struct NodeVar {
    struct NodeVar* prev;
    void* data;
    struct NodeVar* next;
} NodeVar;

typedef struct LL {
    Arena* memory_pool;
    void* head;
    Type type;
    size_t size;
    void* tail;
} LL;

typedef struct CLL {
    Arena* memory_pool;
    void* head;
    Type type;
    size_t size;
} CLL;

/* Linked List Functions */
extern LL* InitList ( void* data, Type t ); /* Init Linked List */
extern void AddNode ( LL* list, void* data ); /* Add node to head */
extern void RemoveNode ( void* Tail, void* data, Type t ); /* Remove node to tail */
extern void* GetLastNode (void* Tail); /* Return ptr to last node */

/* Circular Linked List Functions */


#endif //MYCODEBASE_DSA_H
