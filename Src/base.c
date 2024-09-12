//
// Created by angel on 25/08/24.
//

#include "base.h"

void log_error ( const char* message ) { fprintf (stderr, "[ERROR] : %s\n", message); }
void log_info ( const char* message ) { printf ("[INFO] : %s\n", message); }

void* safe_malloc ( const size_t size ) {
    void* ptr = malloc(size);
    if ( ptr == NULL ) {
        log_error("Error when allocating memory");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void safe_free ( void* ptr ) { ptr != NULL ? free(ptr) : log_error("ptr is NULL"); }

void* safe_realloc ( void* ptr, const size_t size ) {
    void* tmp = ptr;
    ptr = realloc(ptr, size);
    if ( ptr == NULL ) {
        safe_free(tmp);
        log_error("Error when reallocating memory");
        exit(EXIT_FAILURE);
    }
    return ptr;
}