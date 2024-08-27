cmake_minimum_required(VERSION 3.5)
project(MyCodeBase)

set(C_MAKE_C_STANDARD 21)

include_directories(Include)
file(GLOB SOURCES "Src/*.c")

add_library(mycodebase STATIC ${SOURCES}
        Include/memory.h
        Include/utilities.h
        Include/dsa.h
        Src/memory.c
        Src/utilities.c
        Src/dsa.c
)
add_executable(example Examples/main.c
        Include/memory.h
        Include/utilities.h
        Include/dsa.h
        Src/memory.c
        Src/utilities.c
        Src/dsa.c
        Include/base.h
        Src/base.c
)