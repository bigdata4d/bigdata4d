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
target_link_libraries(helloworld bigdata4d ${LIBS})

add_executable(simple simple/simple.cxx simple/SimpleApplication.cxx)
target_link_libraries(simple bigdata4d ${LIBS})

add_executable(operators operators/operators.cxx)
target_link_libraries(operators bigdata4d ${LIBS})

add_executable(timer timer/timer.cxx)
target_link_libraries(timer bigdata4d ${LIBS})
