
/*
 * @author: Angel Castillo @date: 30/08/2024
 *
 * In this file are written the basic Data Structures Definitions and Implementations (Macros):
 *
 *  - Double Linked List (DLL)
 *  - Stack (Single Linked List)
 *  - Queue (Single Linked List)
 *  - Vector (Dynamic Size Array)
 *
 * Every struct is going to have an explanation for every struct member.
 *
 */

/*
 * TODO: Angel Castillo { FIXME: -> Type declarations inside macros -> Print data }
 *
 *
 * */

#ifndef MYCODEBASE_DS_H
#define MYCODEBASE_DS_H

#include "memory.h"
#include <stdbool.h>

#define print( data ) _Generic((data), \
    int: printf( "%d", data ), \
    float: printf( "%f", data ), \
    double: printf("%f", data), \
    char: printf("%c", data), \
    char*: printf("%s", data),   \
    void*: printf("%p", data),\
    default: printf("WTF?\n") \
);

#define printNode( Node ) _Generic((Node->data), \
    int: printf( "->{ %d }<-", ((Node)->data) ),    \
    float: printf( "->{ %f }<-", ((Node)->data) ),   \
    double: printf( "->{ %f }<-", ((Node)->data) ),  \
    char: printf( "->{ %c }<-", ((Node)->data) ),    \
    char*: printf( "->{ %s }<-", ((Node)->data) ),  \
    void*: printf( "->{ %p } <-", ((Node)->data) ),   \
    default: printf("Data is not a primary type\n") \
);

/* Here Tmp has to be a node that always points to the original head other ways behaviour is not how is expected to be */
#define PushBack( Tail, Node, Tmp ) \
	if ( (Tail) == NULL ) { \
		if ((Tmp) != NULL) { \
			((Node)->prev) = (Tmp); \
			((Tmp)->next) = (Node); \
		} \
		(Tail) = (Node); \
	}\
	else { \
		((Tail)->next) = (Node); \
		((Node)->prev) = (Tail); \
		(Tail) = (Node); \
	}\

#define PushFront( Head, Node ) \
	if ( (Head) == NULL )  (Head) = (Node); \
	else { \
		((Node)->next) = (Head); \
		((Head)->prev) = (Node); \
		(Head) = (Node); \
	}\

/* On the next macros the var "Freed" stands for the case where you want the node being freed */
#define PopFront( Head, Freed ) \
	if ( (Freed) ) { \
		(Head) = ((Head)->next); \
		safe_free(((Head)->prev)); \
	} \
	else { \
		(Head) = ((Head)->next); \
		((Head)->prev) = NULL; \
	}\

#define PopBack( Tail, Freed ) \
	if ( (Freed) ) { \
		(Tail) = ((Tail)->prev); \
		safe_free(((Tail)->next)); \
	} \
	else { \
		(Tail) = ((Tail)->prev); \
		((Tail)->next) = NULL; \
	}\

/*
 * @author: Angel Castillo @date: 30/08/2024
 * Every Node-like struct has three members:
 *
 *  - prev
 *  - data
 *  - next
 *
 * prev is a Node-like pointer to a left Node
 * next is a Node-like pointer to a right Node
 * data is variable that stores what you want.
 */

#define NODE( type ) \
	typedef struct Node##type { \
		struct Node##type* prev; \
		type data; \
		struct Node##type* next; \
	} Node##type; \
	\
	static inline Node##type* InitNode##type ( type data ) { \
		Node##type* node = (Node##type*) safe_malloc(sizeof(Node##type));  \
		assert(node != NULL); \
		node->next = NULL;\
		node->prev = NULL; \
		node->data = data; \
		return node; \
	}\
	\
	static inline Node##type* InitNodeList##type ( Arena* mem, type data ) { \
		assert( mem != NULL ); \
		Node##type* node = (Node##type*) ArenaAlloc(mem, sizeof(Node##type), DYNAMIC); \
		assert(node != NULL); \
		node->next = NULL; \
		node->prev = NULL; \
		node->data = data; \
		return node; \
	} \
	\
	static inline void PrintNode##type ( Node##type* node ) {\
		printNode(node) \
	}

/*
 * @author: Angel Castillo @date: 30/08/2024
 *
 * DLL stands for Double Linked List. Every DLL-like struct has 5 members:
 * - mem : a memory pool to store every node
 * - head : top of the list
 * - tail: bottom of the list
 * - tmp: pointer, always points to original head
 * - size: how many nodes has linked
 *
 */

#define DLL_INIT( type ) \
	typedef struct DLL##type { \
		Arena* mem; \
		Node##type* head; \
		Node##type* tail; \
		Node##type* tmp; \
		size_t size; \
	} DLL##type;  \
	\
	static inline DLL##type* InitDLL##type ( type data ) { \
		DLL##type* dll = safe_malloc(sizeof(DLL##type)); \
		dll->mem = CreateArena( 10 * sizeof(Node##type) ); \
		dll->head = InitNodeList##type(dll->mem, data); \
		dll->head->next = dll->tail; \
		dll->tail = NULL; \
		dll->tmp = dll->head; \
		dll->size = 1; \
		return dll; \
	} \
	\

#define DLLPushFront( DLL, type, data ) \
	if ( (DLL) != NULL ) { \
		Node##type* node = InitNodeList##type(((DLL)->mem), (data)); \
		PushFront(((DLL)->head), node); \
		((DLL)->head) = (node); \
		((DLL)->size)++;  \
	}\

#define DLLPushBack( DLL, type, data ) \
	if ( (DLL) != NULL ) { \
		Node##type* node = InitNodeList##type(((DLL)->mem), data); \
		PushBack(((DLL)->tail), node, ((DLL)->tmp)); \
		((DLL)->tail) = (node);\
		((DLL)->size)++;\
	} \

#define DLLGetNode( DLL, index, ptr ) \
        while ( (DLL) != NULL && ((DLL)->tmp) != NULL && index-- ) (tmp) = ((tmp)->next); \
        (ptr) = (void *)(tmp); \
        (tmp) = ((DLL)->head); \

#define DLLPopFront( DLL ) \
	if ( ((DLL) != NULL) && (((DLL)->head) != NULL) ) {\
		if (((DLL)->size) == 1) ((DLL)->head) = ((DLL)->tail) = NULL; \
		else PopFront(((DLL)->head), 0);                  \
		((DLL)->size)--; \
	}\

#define DLLPopBack( DLL ) \
	if (((DLL) != NULL) && (((DLL)->tail) != NULL)) { \
		if (((DLL)->size) == 1) ((DLL)->head) = ((DLL)->tail) = NULL; \
		else PopBack(((DLL)->tail), 0); \
		((DLL)->size)--;        \
	} \

/* Warning, you're freeing the entire DLL */
#define CloseDLL(DLL) \
	if ((DLL) != NULL) { \
		((DLL)->head) = NULL; \
		((DLL)->tail) = NULL; \
		((DLL)->tmp) = NULL; \
		DestroyArena(((DLL)->mem)); \
		((DLL)->size) = 0; \
		safe_free((DLL)); \
	}

/*
 * @author: Angel Castillo @date: 30/08/2024
 *
 *  Every Stack-like struct has 3 members:
 *  - head: top of the stack
 *  - size: how many nodes are in the stack
 *  - tmp: an auxiliary ptr
 *
 */

#define STACK(type) \
	typedef struct Stack##type { \
		Node##type* head; \
		Node##type* tmp; \
		size_t size; \
	} Stack##type; \
	\
	static inline Stack##type* InitStack##type ( type data ) { \
		Stack##type* s = safe_malloc(sizeof(Stack##type));\
		s->head = InitNode##type(data); \
		s->tmp = s->head; \
		s->size = 1; \
		return s;\
	}\

#define IsStackEmpty(Stack) (bool)((Stack)->size == 0)

#define StackPush( Stack, type, data ) \
	if ( (Stack) != NULL ) { \
		if ( ((Stack)->head) == NULL ) ((Stack)->head) = InitNode##type(data); \
		else { \
			Node##type* node = InitNode##type(data); \
			PushFront(((Stack)->head), (node)); \
			((Stack)->head) = (node); \
			((Stack)->tmp) = ((Stack)->head); \
		} \
		((Stack)->size)++; \
	}\

#define StackPop( Stack ) \
	if ( (Stack) != NULL ) { \
		if (((Stack)->size) == 1) safe_free(((Stack)->head)); \
		else { \
			PopFront(((Stack)->head), 1); \
			((Stack)->tmp) = ((Stack)->head); \
		} \
		((Stack)->size)--; \
	}\

#define StackPrint( Stack ) \
	if ( (Stack) != NULL ) { \
		while ( ((Stack)->tmp) != NULL ) { \
			printNode(((Stack)->tmp)); \
			((Stack)->tmp) = (((Stack)->tmp)->next); \
		} \
		((Stack)->tmp) = ((Stack)->head); \
	} \

#define StackHeadData( Stack, type ) (type)(((Stack)->head)->data);

#define StackHead( Stack ) (void*)((Stack)->head)

#define CloseStack( Stack, type ) \
	if ( (Stack) != NULL ) { \
		bool b = IsStackEmpty(Stack); \
		while (!b) { \
			StackPop(Stack);\
			b = IsStackEmpty(Stack); \
		} \
		safe_free((Stack)); \
	} \

/*
 * @author: Angel Castillo @date: 02/09/2024
 *
 * Every Queue-like struct has 4 members:
 *
 * - head: top of the queue
 * - tail: bottom of the queue
 * - tmp: an auxiliary node
 * - size: how many nodes are in the queue
 */

#define QUEUE(type) \
	typedef struct Queue##type { \
		Node##type* head; \
		Node##type* tail; \
		Node##type* tmp; \
		size_t size; \
	} Queue##type;  \
	\
	static inline Queue##type* InitQueue##type ( type data ) { \
		Queue##type* q = safe_malloc(sizeof(Queue##type));\
		q->head = q->tail = InitNode##type(data); \
		q->tmp = q->head; \
		q->size = 1; \
		return q; \
	} \

#define QueuePush(Queue, type, data) \
	if ((Queue) != NULL) { \
		Node##type* node = InitNode##type(data); \
		PushBack( ((Queue)->tail), (node), ((Queue)->tmp) ); \
		((Queue)->tail) = (node); \
		if (((Queue)->head) == NULL) { ((Queue)->tmp) = ((Queue)->head) = ((Queue)->tail); }\
		((Queue)->size)++; \
	} \

#define QueuePop(Queue) \
	if ((Queue) != NULL) {\
		if (((Queue)->size) == 1) { ((Queue)->tmp) = ((Queue)->head) = ((Queue)->tail) = NULL;  } \
		else { \
			void* tmp = (((Queue)->head)->next); \
			PopFront(((Queue)->head), 1); \
			((Queue)->head) = tmp; \
			((Queue)->tmp) = ((Queue)->head); \
			((Queue)->size)--; \
		}\
	}

#define QueuePrint(Queue) \
	if ((Queue) != NULL) { \
		while (((Queue)->tmp) != NULL) { \
			printNode(((Queue)->tmp)); \
			((Queue)->tmp) = (((Queue)->tmp)->next); \
		} \
		((Queue)->tmp) = ((Queue)->head); \
	} \

/*
 * @author: Angel Castillo @date: 09/09/2024
 *
 * Every Vector-like struct has 4 members:
 *
 * - array: a ptr to the firs element of the array
 * - size: used memory cells of the array
 * - current_last: last array concurrent element's index
 * - offset: usable memory cells of the array
 *
 */

#define VECTOR(type) \
    typedef struct Vector##type { \
        type* array; \
        uint128 size;\
        uint128 current_last; \
        uint128 offset; \
    } Vector##type;  \
    \
    static inline Vector##type* InitVector##type ( type data, size_t size ) { \
        Vector##type* v = safe_malloc(sizeof(Vector##type)); \
        v->array = size == 0 || size < 0 ? safe_malloc( 10 * sizeof(type) ) : safe_malloc( size * sizeof(type) ); \
        v->offset = size == 0 || size < 0 ? 10 : size;  \
        v->array[0] = data; \
        v->size = 1; \
        v->current_last = 0; \
        return v; \
    }

#define VectorPush( Vector, data ) \
    if ((Vector) != NULL) {        \
        if ( ((Vector)->current_last) < ((Vector)->offset) - 1 ) \
            ((Vector)->array[((Vector)->current_last++)]) = data; \
        else {                     \
            ((Vector)->array) = safe_realloc( ((Vector)->array), ((Vector)->offset) * 2 * sizeof(((Vector)->array[0]) )); \
            ((Vector)->offset) *= 2;                         \
            ((Vector)->array[((Vector)->current_last++)]) = data; \
        }                          \
        ((Vector)->size)++; \
    }

#define VectorPushAtIndex( Vector, index, data ) \
    if ( (Vector) != NULL ) {                    \
         \
    }\

#define VectorGet( Vector, index, type ) (type)((Vector)->array[index < 0 || index > ((Vector)->size) ? 0 : index]) \

#define VectorPop( Vector, type ) \
    if ( (Vector) != NULL ) { \
        ((Vector)->array[((Vector)->current_last)]) = (type){0}; \
        ((Vector)->size)--;       \
        ((Vector)->current_last)--; \
    }

#define VectorFree( Vector, type ) \
    if ( (Vector) != NULL ) {      \
       if ( ((Vector)->size) > 1 ) for ( uint128 i = 0; i < ((Vector)->size); i++ ) ((Vector)->array[i]) = (type){0};  \
       else ((Vector)->array[0]) = (type){0};                                                                          \
       ((Vector)->size) = 0; \
       ((Vector)->offset) = 0; \
       safe_free(((Vector)->array)); \
       safe_free((Vector)); \
    }

#define NEW_ST_DSA(type) \
	NODE(type); \
	DLL_INIT(type); \
	STACK(type); \
	QUEUE(type); \
    VECTOR(type);

NEW_ST_DSA(int)
NEW_ST_DSA(float)
NEW_ST_DSA(double)
NEW_ST_DSA(bool)
NEW_ST_DSA(char)
NEW_ST_DSA(string)
NEW_ST_DSA(object)

#endif //MYCODEBASE_DS_H
