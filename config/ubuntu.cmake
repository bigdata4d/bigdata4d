# Ubuntu 14.04
set(ENV{CXX} mpicxx)
# set(ENV{CXX} g++)
# set(ENV{CXX} clang++)

set(USER_CXX_FLAGS "-std=c++11")
set(USER_CXX_FLAGS_RELEASE "-O3 -ffast-math -mtune=native -march=native")
set(USER_CXX_FLAGS_DEBUG "-O0 -g -Wall -Wno-unknown-pragmas")

add_definitions(-DRESTRICTKEYWORD=__restrict__)
