include_directories(${INCLUDE_DIRS} "../include")

# retrieve the git hash from the current commit
# find_package(Git)
# if(GIT_EXECUTABLE)
#   exec_program(git ${CMAKE_CURRENT_SOURCE_DIR} ARGS "describe --dirty" OUTPUT_VARIABLE GITHASH RETURN_VALUE GITRETURN)
#   if(NOT GITRETURN MATCHES 0)
#     set(GITHASH "not available")
#   endif()
# else()
#   set(GITHASH "not available")
# endif()
# 
# message(STATUS "Git hash " ${GITHASH})

# send a precompiler statement replacing the git hash
# add_definitions(-DGITHASH="${GITHASH}")
add_executable(helloworld helloworld/helloworld.cxx)
target_link_libraries(helloworld ${LIBS})

add_executable(simple simple/simple.cxx simple/SimpleApplication.cxx)
target_link_libraries(simple ${LIBS})

add_executable(operators operators/operators.cxx)
target_link_libraries(operators ${LIBS})

add_executable(timer timer/timer.cxx)
target_link_libraries(timer ${LIBS})

#add_executable(diffusion diffusion/diffusion.cxx)
#target_link_libraries(diffusion bigdata4d ${LIBS})

if(USECUDA)
  cuda_add_executable(timer_cuda timer_cuda/timer_cuda.cu timer_cuda/timer_cuda.cxx)
  cuda_add_cublas_to_target(timer_cuda)
  target_link_libraries(timer_cuda ${LIBS})

  cuda_add_executable(diffusion diffusion/diffusion.cu)
  cuda_add_cublas_to_target(diffusion)
  target_link_libraries(diffusion ${LIBS})
endif()
