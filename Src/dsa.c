//
// Created by angel on 19/08/24.
//

#include "dsa.h"

static Arena *memory_pool = NULL; /* Stores pointers */

/*
 * This functions purpose is to initialize, close or check initialize
 * of memory_pool which is an Arena* where these structs are going to store
 * itself and its data.
 */

void dsa_init ( void ) { memory_pool = memory_pool == NULL ? CreateArena(512) : memory_pool; }
void dsa_close ( void ) { DestroyArena(memory_pool); }
void check_dsa_init ( void ) { assert( memory_pool != NULL ); }

/*
 * The Data struct is for general data management. For simplicity is better to
 * just modify Data struct to store whatever you want. These are its functions.
 * You could modify however you want.
 */

static void InitData( Data* data, void* store );
static void PrintData ( const Data* data );

static void InitData ( Data* data, void* store ) { data->num = *(int*)store; }

static void PrintData ( const Data* data ) { printf(" <- { %d } -> ", data->num); }

/*
 * The Node struct is the base for every Stack, Queue, Double Linked List and Circular Double
 * Linked List. I'm not implementing a Single Linked List 'cause is just too limited. Here are
 * the basic Node functions. Do not modify them, unless you know what you're doing or your project
 * (or your Data struct implementation) needs it.
 */

static Node* InitNodeR ( DLL* list, void* data );

Node* InitNode ( void* data ) {
	check_dsa_init();
    Node* node = ArenaAlloc(memory_pool, sizeof(Node), DYNAMIC);
    data == NULL ? node->data.num = 0 : InitData(&node->data, data);
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void PrintNode ( const Node* node ) { PrintData(&node->data); }

/*
 * The DLL stands for Double Linked List. This is a struct with three things:
 *
 * - Head (The "top" of the list)
 * - Tail (The "bottom" of the list)
 * - Size (How many nodes does it have linked)
 *
 * To visualize it just Imagine this:
 *
 *  { NULL } <- { data_1 } <-> { data_2 } <-> { data_3 } -> { NULL }
 *                  ^                             ^
 *                 Head                          Tail
 *
 *  Where {} are pointers that point to data_i and the arrows are also pointers that point
 *  to the concurrent nodes.
 */

DLL* InitDLL ( void* data ) {
	check_dsa_init();
	DLL* dll = ArenaAlloc(memory_pool, sizeof(dll) + 10*sizeof(Node), DYNAMIC);
	dll->head = InitNode(data);
	dll->head->next = dll->tail;
	dll->head->prev = NULL;
	dll->tail = NULL;
	dll->size++;
	return dll;
}

void DLLPushBack ( DLL* list, void* data ) {
	assert( list != NULL && data != NULL );
	Node* new_node = InitNode(data);
	if (list->tail == NULL) {
		list->tail = new_node;
		list->tail->prev = list->head;
		list->head->next = list->tail;
	}
	else {
		list->tail->next = new_node;
		new_node->prev = list->tail;
		list->tail = new_node;
	}
}

void DLLPushFront ( DLL* list, void* data ) {
	assert( list != NULL && data != NULL );
	Node* new_node = InitNode(data);
	new_node->next = list->head;
	list->head->prev = new_node;
	list->head = new_node;
}

void DLLPopBack ( DLL* list ) {
	assert( list != NULL && list->tail != NULL );
	list->tail = list->tail->prev;
	list->tail->next = NULL;
}

void DLLPopFront ( DLL* list ) {
	assert( list != NULL );
	list->head = list->head->next;
	list->head->prev = NULL;
}

void DLLPrint ( DLL* list ) {
	assert(list != NULL);
	printf("DLL: \n");
	Node* tmp = list->head;
	while ( tmp != NULL ) {
		PrintNode(tmp);
		tmp = tmp->next;
	}
	printf("\n");
}