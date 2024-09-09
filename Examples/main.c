// Created by angel on 19/08/24.

#include <stdio.h>
#include "dsa.h"

void PrintVectorInfo ( Vectorstring* v ) {
    printf("size = %llu \n"
           "offset = %llu \n"
           "array ptr = %p\n", v->size, v->offset, v->array);
}

int main ( void ) {
    Vectorstring* v = InitVectorstring("Hello world\n", 0);
    VectorPush(v, "I'm Angel\n");
    VectorPush(v, "I'm studying computer science\n");
    VectorPush(v, "My lastname is Castillo\n");
    PrintVectorInfo(v);

    for ( uint128 i = v->size; i < 20; i++ )
           VectorPush(v, "0\n");

    VectorPush(v, "Hello there!\n")

    for ( int i = 0; i < v->size; i++ ) printf("%s", v->array[i]);

    printf("%s", VectorGet(v, 23, string));

    VectorPop(v, string)

    for ( int i = 0; i < v->size; i++ ) printf("%s", VectorGet(v, i, string));

    PrintVectorInfo(v);

    return 0;
}