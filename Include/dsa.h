//
// Created by angel on 19/08/24.
//

#ifndef MYCODEBASE_DSA_H
#define MYCODEBASE_DSA_H

#include "memory.h"

extern void dsa_init ( void );
extern void dsa_close ( void );
extern void check_dsa_init ( void );

typedef enum Type {
    INT = 0,
    FLOAT = 1,
    DOUBLE = 2,
    STRING = 3,
    VAR = 4 /* a void* not recommendable if you're not allocating structures in the node */
} Type;

/*
 * It's better to create from scratch an LLStruct with
 * a struct data you want to use instead of using the NodeVar.
 * That's often better for memory and execution performance.
 */

#define DLLPushFront(h, n) \
    if ((h) == NULL) {  \
        log_error("You can't push into a NULL list"); \
        exit(EXIT_FAILURE); \
    } \
    (n)->next = (h); \
    (h)->prev = (n); \
    (h) = (n);

#define DLLPushBack(h, l, n) \
    if ( (h) == NULL ) { \
        log_error("You can't push into a NULL list"); \
        exit(EXIT_FAILURE); \
    } \
    (l)->next = (n);  \
    (n)->prev = (l); \
    (l) = (n);

#define DLLPopFront(h) \
    if ( (h) == NULL ) { \
        log_error("You can't pop from a NULL list"); \
        exit(EXIT_FAILURE); \
    } \
    (h) = ((h)->next); \

#define DLLPopBack(l) \
    if ( (l) == NULL ) { \
        log_error("You can't pop from a NULL tail"); \
        exit(EXIT_FAILURE) \
    } \
    (l) = ((l)->prev);

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

extern void* NodeInit( void* data, Type t );

extern void PrintList ( void* head, Type t );

#endif //MYCODEBASE_DSA_H
