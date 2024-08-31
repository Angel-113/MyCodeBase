// Created by angel on 19/08/24.

#include <stdio.h>
#include "dsa.h"

include_dsa();

int main ( void ) {
	DLLint* list = InitDLLint(4);
	PrintDLLint(list);
	PushFrontDLLint(list, 5);
	PrintDLLint(list);
	PushBackDLLint(list, 6);
	PrintDLLint(list);
	PushBackDLLint(list, 7);
	PrintDLLint(list);
    return 0;
}