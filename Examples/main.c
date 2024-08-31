// Created by angel on 19/08/24.

#include <stdio.h>
#include "dsa.h"

int main ( void ) {

	dsa_init();

	DLL* list = InitDLL(NULL);

	for ( int i = 0; i < 100; i++ ) {
		int n = i + 1;
		DLLPushBack(list, &n);
	}

	DLLPrint(list);

	for ( int i = 0; i < 100; i++ ) DLLPopBack(list);

	DLLPrint(list);

    return 0;
}