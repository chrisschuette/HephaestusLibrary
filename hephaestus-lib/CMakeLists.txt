cmake_minimum_required (VERSION 2.6)
file(GLOB_RECURSE hephaestus_SRC
    "src/*.h"
    "src/*.cpp"
)
set(CMAKE_MODULE_PATH
${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

add_library(hephaestus_static STATIC ${hephaestus_SRC})

# freetype for opengl font rendering
find_package (Freetype REQUIRED)
if (FREETYPE_FOUND)
  include_directories(${FREETYPE_INCLUDE_DIRS})
  target_link_libraries(hephaestus_static ${FREETYPE_LIBRARY})
  endif (FREETYPE_FOUND)

#boost
set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME ON) 
find_package(Boost 1.45.0 COMPONENTS system filesystem thread REQUIRED) 
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    target_link_libraries(hephaestus_static ${Boost_LIBRARIES})
endif()

#openGL
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
   include_directories(${OPENGL_INCLUDE_DIR})
   TARGET_LINK_LIBRARIES(hephaestus_static ${OPENGL_LIBRARIES})
endif (OPENGL_FOUND)

#GLEW
find_package( GLEW REQUIRED )
if(GLEW_FOUND)
 include_directories(${GLEW_INCLUDE_DIR})
 target_link_libraries(hephaestus_static ${GLEW_LIBRARIES})
endif(GLEW_FOUND)

#DevIL
find_package( DevIL )
if(IL_FOUND)
 include_directories(${IL_INCLUDE_DIR})
  target_link_libraries(hephaestus_static ${IL_LIBRARIES})
endif(IL_FOUND)

#Box2D
find_package(Box2D REQUIRED)
if(BOX2D_FOUND)
 include_directories(${BOX2D_INCLUDE_DIR})
 target_link_libraries(hephaestus_static ${BOX2D_LIBRARIES})
endif(BOX2D_FOUND)

#CONFIG++
find_package(Config++ REQUIRED)
if(CONFIG++_FOUND)
 message("CONFIG++: " ${CONFIG++_LIBRARY})
 include_directories(${CONFIG++_INCLUDE_DIR})
 target_link_libraries(hephaestus_static ${CONFIG++_LIBRARY})
endif(CONFIG++_FOUND)

#pthread
find_package (Threads REQUIRED)

#OpenAL
find_package(OpenAL REQUIRED)
if(OPENAL_FOUND)
  include_directories(${OPENAL_INCLUDE_DIR} )
 target_link_libraries(hephaestus_static ${OPENAL_LIBRARIES})
endif(OPENAL_FOUND)

#VorbisFile
find_package(VorbisFile REQUIRED)
if(VorbisFile_FOUND)
  include_directories(${VorbisFile_INCLUDE_DIR} )
  target_link_libraries(hephaestus_static ${VorbisFile_LIBRARIES})
endif(VorbisFile_FOUND)

#GLFW3
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(hephaestus_static ${GLFW_LIBRARIES})

#X11
find_package(X11)
if(X11_FOUND)
message(${X11_LIBRARIES})
include_directories(${X11_INCLUDE_DIRS})
target_link_libraries(hephaestus_static ${X11_LIBRARIES})
endif(X11_FOUND)


# Set additional libs
set( ADDITIONAL_LIBS 
     -lGLEW
     -lGLU 
     -lglfw3
     -pthread
     -lrt
     -lXinerama
     -lXrandr
     -lXxf86vm
     -lXi
)
target_link_libraries(hephaestus_static ${ADDITIONAL_LIBS})
