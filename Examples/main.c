// Created by angel on 19/08/24.

#include <stdio.h>
#include "dsa.h"

typedef struct box {
	float x;
	float y;
	unsigned int height;
	unsigned int width;
} box;

NEW_ST_DSA(box);

int main ( void ) {
	DLLint *List = InitDLLint(4);
	DLLPushFront(List, int, 5);

	Nodeint* tmp = List->head;
	while ( tmp != NULL ) {
		printf("%d\n", tmp->data);
		tmp = tmp->next;
	}
	DLLPushBack(List, int, 3);
	tmp = List->head;
	while ( tmp != NULL ) {
		printf("%d\n", tmp->data);
		tmp = tmp->next;
	}

	DLLPopBack(List);
	DLLPopFront(List);

	tmp = List->head;
	while ( tmp != NULL ) {
		printf("%d\n", tmp->data);
		tmp = tmp->next;
	}

	DLLPopBack(List);
	DLLPopFront(List);

    return 0;
}