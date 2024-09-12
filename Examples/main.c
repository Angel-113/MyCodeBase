// Created by angel on 19/08/24.

#include <stdio.h>
#include "ds.h"
#include "adv_ds.h"

int main (void ) {

    DLLint* list = InitDLLint(4);

    DLLPushBack(list, int, 5)

    while ( list->tmp != NULL ) {
        printNode(list->tmp)
        list->tmp = list->tmp->next;
    }

    return 0;
}