# MacBook
# parallel build
#set(ENV{CXX} mpicxx)
#set(ENV{CC} mpicc)

# serial build
set(ENV{CXX} g++)
set(ENV{CC} gcc)

set(USER_C_FLAGS "-std=c++11")
set(USER_C_FLAGS_RELEASE "-O3 -ffast-math -mtune=native -march=native")
set(USER_C_FLAGS_DEBUG "-O0 -g -Wall -Wno-unknown-pragmas")

set(USER_CXX_FLAGS "-std=c++11")
set(USER_CXX_FLAGS_RELEASE "-O3 -ffast-math -mtune=native -march=native")
set(USER_CXX_FLAGS_DEBUG "-O0 -g -Wall -Wno-unknown-pragmas")

if(USECUDA)
  set(CUDA_PROPAGATE_HOST_FLAGS OFF)
  set(CUDA_NVCC_FLAGS "-arch=sm_30")
endif()

add_definitions(-DRESTRICTKEYWORD=__restrict__)

