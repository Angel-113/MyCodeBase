
/*
 * @author: Angel Castillo @date: 30/08/2024
 *
 * In this file are written the basic Data Structures Definitions and Implementations (Macros):
 *
 *  - Double Linked List (DLL)
 *  - Stack (Single Linked List)
 *  - Queue (Single Linked List)
 *  - Circular Double Linked List (CDLL)
 *
 * Every struct is going to have an explanation for every struct member.
 *
 */

#ifndef MYCODEBASE_DSA_H
#define MYCODEBASE_DSA_H

#include "memory.h"
#include <stdbool.h>

/* Here Tmp has to be a node that always points to the original head other ways behaviour is not how is expected to be */
#define PushBack( Tail, Node, Tmp ) \
	if ( (Tail) == NULL ) { \
		((Node)->prev) = (Tmp); \
		((Tmp)->next) = (Node); \
		(Tail) = (Node); \
	} \
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
	static inline void PrintNode##type ( Node##type* node ) { \
		printf( "->{ %p }<-", node ); \
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

#define DLLPopFront( DLL ) \
	if ( ((DLL) != NULL) && (((DLL)->head) != NULL) ) {\
		if (((DLL)->size) == 1) ((DLL)->head) = ((DLL)->tail) = NULL; \
		else PopFront(((DLL)->head), 0); \
		((DLL)->size)--; \
	}\

#define DLLPopBack( DLL ) \
	if (((DLL) != NULL) && (((DLL)->tail) != NULL)) { \
		if (((DLL)->size) == 1) ((DLL)->head) = ((DLL)->tail) = NULL; \
		else PopBack(((DLL)->tail), 0); \
		((DLL)->size)--; \
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

#define IsStackEmpty(Stack) (Stack)->size) == 0;

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
			printf("{ %p }\n", ((Stack)->tmp)); \
			((Stack)->tmp) = (((Stack)->tmp)->next); \
		} \
		((Stack)->tmp) = ((Stack)->head); \
	} \

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
 *
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
		q->tmp = q->tail; \
		q->size = 1; \
		return q; \
	} \

#define NEW_ST_DSA(type) \
	NODE(type);\
	DLL_INIT(type);\
	STACK(type);\
	QUEUE(type);\

NEW_ST_DSA(int);
NEW_ST_DSA(float);
NEW_ST_DSA(double);
NEW_ST_DSA(bool);
NEW_ST_DSA(char);
NEW_ST_DSA(string);
NEW_ST_DSA(object)


#endif //MYCODEBASE_DSA_H
