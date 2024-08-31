
/*
 * @author: Angel Castillo @date: 30/08/2024
 *
 * In this file are written the basic Data Structures Definitions:
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

/*
 * @author: Angel Castillo @date: 30/08/2024
 * Every Node like struct has three members:
 *
 *  - prev
 *  - data
 *  - next
 *
 * prev is a Node like pointer to a left Node
 * next is a Node like pointer to a right Node
 * data is variable that stores what you want.
 */

#define NODE(type) \
	typedef struct Node##type { \
		struct Node##type* prev; \
		type data; \
		struct Node##type* next; \
	} Node##type; \
	\
	Node##type* InitNode##type(type data) { \
		Node##type* node = (Node##type*) safe_malloc(sizeof(Node##type));  \
		assert(node != NULL); \
		node->next = NULL;\
		node->prev = NULL; \
		node->data = data; \
		return node; \
	}\
	\
	Node##type* InitNodeList##type(Arena* mem, type data) { \
		assert( mem != NULL ); \
		Node##type* node = (Node##type*) ArenaAlloc(mem, sizeof(Node##type), DYNAMIC); \
		assert(node != NULL); \
		node->next = NULL; \
		node->prev = NULL; \
		node->data = data; \
		return node; \
	} \
	\
	void PrintNode##type(Node##type* node) { \
		printf( "->{ %p }<-", node ); \
	}


#define NODE_CHAR() \
	typedef struct NodeString { \
		struct NodeString* prev; \
		char* data; \
		struct NodeString* next; \
	} NodeString; \
	\
	NodeString* InitNodeString(char* data) { \
		NodeString* node = (NodeString*) safe_malloc(sizeof(NodeString)); \
		assert(node != NULL); \
		node->next = NULL;\
		node->prev = NULL; \
		node->data = data; \
		return node; \
	}\
	NodeString* InitNodeStringList(Arena* mem, char* data) { \
		NodeString* node = (NodeString*) ArenaAlloc(mem, sizeof(NodeString), DYNAMIC);\
		assert(node != NULL); \
		node->next = NULL; \
		node->prev = NULL; \
		node->data = data; \
		return node; \
	}\

#define NODE_INIT() \
	NODE(int); \
	NODE(float); \
	NODE(double); \
	NODE(bool); \
	NODE(char) \
	NODE_CHAR();

/*
 * @author: Angel Castillo @date: 30/08/2024
 *
 * DLL stands for Double Linked List. Every DLL like struct has four member:
 * - mem : a memory pool to store every node
 * - head : top of the list
 * - tail: bottom of the list
 * - size: how many nodes has linked
 *
 */

#define DLL_INIT(type) \
	typedef struct DLL##type { \
		Arena* mem; \
		Node##type* head; \
		Node##type* tail; \
		Node##type* tmp; \
		size_t size; \
	} DLL##type;  \
	\
	DLL##type* InitDLL##type( type data ) { \
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
	void PushFrontDLL##type( DLL##type* list, type data) { \
		assert(list != NULL && list->head != NULL && list->mem != NULL ); \
		Node##type* new_node = InitNodeList##type(list->mem, data); \
		((new_node)->next) = ((list)->head); \
		(((list)->head)->prev) = (new_node); \
		((list)->head) = (new_node); \
		((list)->size)++; \
	} \
	\
	void PushBackDLL##type ( DLL##type* list, type data ) {\
		assert(list != NULL && list->mem != NULL);	 \
		Node##type* node = InitNodeList##type(list->mem, data); \
		if ( list->tail == NULL ) { node->prev = list->tmp; list->tmp->next = node; list->tail = node;} \
		else { \
			list->tail->next = node; \
			node->prev = list->tail; \
			list->tail = node; \
		} \
		list->size++; \
	} \
	\
	void PrintDLL##type(DLL##type* list) { \
		assert(list != NULL); \
		Node##type* tmp = list->head; \
		printf("DLL : \t\t size = %zu \n", list->size); \
		while ( tmp != NULL ) { \
			PrintNode##type(tmp); 	\
			(tmp) = ((tmp)->next); \
		} \
		printf("\n"); \
	} \



/*
 * @author: Angel Castillo @date: 30/08/2024
 *
 *  Every Stack like struct has 2 members:
 *  - head: top of the stack
 *  - size: how many nodes are in the stack
 *
 */

#define include_dsa() \
	NODE_INIT(); \
	DLL_INIT(int); \
	DLL_INIT(float) \
	DLL_INIT(double) \
	DLL_INIT(bool) \
	DLL_INIT(char) \

#endif //MYCODEBASE_DSA_H
