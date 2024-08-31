// Created by angel on 19/08/24.

#ifndef MYCODEBASE_DSA_H
#define MYCODEBASE_DSA_H
#include "memory.h"

typedef struct Data { /* Modify this struct to store whatever you want*/
    int num;
} Data;

typedef struct Node {
    struct Node* prev;
    Data data;
    struct Node* next;
} Node;

typedef struct DLL {
    Node* head;
    Node* tail;
    size_t size;
} DLL;

typedef struct Stack {
    Node* head;
    size_t size;
} Stack;

typedef struct Queue {
    Node* tail;
    size_t size;
} Queue;

extern void dsa_init ( void );
extern void dsa_close ( void );
extern void check_dsa_init ( void );

extern Node* InitNode ( void* data );
extern void PrintNode ( const Node* node );

extern DLL* InitDLL ( void* data );
extern void DLLPushBack ( DLL* list, void* data );
extern void DLLPushFront ( DLL* list, void* data );
extern void DLLPopBack ( DLL* list );
extern void DLLPopFront ( DLL* list );
extern void DLLPrint ( DLL* list );

#endif //MYCODEBASE_DSA_H
