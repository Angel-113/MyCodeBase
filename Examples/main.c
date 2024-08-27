//
// Created by angel on 19/08/24.
//

#include <stdio.h>
#include "memory.h"
#include "dsa.h"
#include "utilities.h"

int main ( void ) {
    int n = 9;
    dsa_init();
    NodeInt* h = NodeInit(&n, INT);
    NodeInt* n1 = NodeInit(&n, INT);
    DLLPushFront(h, n1);
    DLLPushBack(h, n1, n1); 
    PrintList(h, INT);
    return 0;
}
