# Ubuntu 14.04
#set(ENV{CC}  mpicc )
#set(ENV{CXX} mpicxx)
set(ENV{CC}  gcc)
set(ENV{CXX} g++)

set(USER_CXX_FLAGS "-stdlib=libstdc++ -std=c++11")
set(USER_CXX_FLAGS_RELEASE "-O3 -ffast-math -mtune=native -march=native")
set(USER_CXX_FLAGS_DEBUG "-O0 -g -Wall -Wno-unknown-pragmas")

set(USER_C_FLAGS "-stdlib=libstdc++")
set(USER_C_FLAGS_RELEASE "-O3 -ffast-math -mtune=native -march=native")
set(USER_C_FLAGS_DEBUG "-O0 -g -Wall -Wno-unknown-pragmas")

if(USECUDA)
  set(CUDA_PROPAGATE_HOST_FLAGS OFF)
  set(CUDA_NVCC_FLAGS "-arch=sm_13")
endif()

add_definitions(-DRESTRICTKEYWORD=__restrict__)
