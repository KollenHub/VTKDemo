cmake_minimum_required(VERSION 3.20)

project(VTK_DEMO)

include(cmake/directory.cmake)
include(cmake/package.cmake)

find_package(Qt5 REQUIRED CONFIG COMPONENTS Widgets Core)

find_package(VTK REQUIRED CONFIG COMPONENTS
  CommonColor
  CommonCore
  CommonTransforms
  FiltersSources
  InteractionStyle
  InteractionWidgets
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2)


get_direct_subdirectories(${CMAKE_CURRENT_LIST_DIR} SUB_DIRS)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_CURRENT_LIST_DIR}/bin)

foreach(SUB_DIR ${SUB_DIRS})
  if(EXISTS ${SUB_DIR}/CMakeLists.txt)
    get_filename_component(SUB_DIR_NAME ${SUB_DIR} NAME)
    add_subdirectory(${SUB_DIR_NAME})
  endif()
endforeach()

file(GLOB VTK_DLLS ${CMAKE_CURRENT_LIST_DIR}/bin/vtkCommonCore-*.dll)
if(NOT VTK_DLLS)
  get_filename_component(VTK_BIN_DIR "${VTK_DIR}/../../../bin" ABSOLUTE)
  file(COPY "${VTK_BIN_DIR}"
    DESTINATION "${CMAKE_CURRENT_LIST_DIR}/"
  )
endif()


