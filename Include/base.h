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
typedef unsigned long long int uint128;
typedef unsigned long int uint64;
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef char int8;
typedef short int int16;
typedef long int int32;
typedef long long int int64;

typedef char* string;
typedef void* object; /* ----> When using it as a pointer to any type or any struct */

extern void* safe_malloc ( size_t size );
extern void* safe_realloc ( void* ptr, size_t size );
extern void safe_free ( void* ptr );

extern void log_error ( const char* message );
extern void log_info ( const char* message );

#endif //BASE_H
