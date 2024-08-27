//
// Created by angel on 25/08/24.
//

#ifndef BASE_H
#define BASE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define to_string(expr) #expr

typedef unsigned char byte;

extern void* safe_malloc ( size_t size );
extern void* safe_realloc ( void* ptr, size_t size );
extern void safe_free ( void* ptr );

extern void log_error ( const char* message );
extern void log_info ( const char* message );

#endif //BASE_H
