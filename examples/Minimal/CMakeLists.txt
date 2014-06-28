cmake_minimum_required (VERSION 2.6)
if(POLICY CMP0015)
	cmake_policy(SET CMP0015 OLD)
endif()
file(GLOB_RECURSE Minimal_SRC
    "src/*.h"
    "src/*.cpp"
)
set(CMAKE_MODULE_PATH
${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

include_directories (../../hephaestus-lib/src) 
link_directories (../../hephaestus-lib) 
add_executable(Minimal ${Minimal_SRC})
target_link_libraries (Minimal hephaestus_static) 