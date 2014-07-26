FILE(GLOB sourcefiles "../src/*.cxx")
include_directories(${INCLUDE_DIRS} "../include")

add_library(bigdata4d STATIC ${sourcefiles})
