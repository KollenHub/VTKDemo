cmake_minimum_required(VERSION 3.20)

project(VTK_DEMO)

include(cmake/directory.cmake)
include(cmake/package.cmake)

find_package(Qt5 REQUIRED CONFIG COMPONENTS Widgets Core Gui)

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
  RenderingVolumeOpenGL2
  RenderingOpenGL2
  IOLegacy
  InteractionImage
  IOImport
  CommonExecutionModel
  ImagingSources
  InteractionStyle
  ImagingColor
  ImagingStatistics
  RenderingAnnotation
  ImagingMath
  ImagingGeneral
  ImagingFourier
  FiltersModeling
  IOPLY
  FiltersExtraction
  FiltersGeometry
  IOImage
  FiltersTexture
  RenderingVolume
  GUISupportQt
)

if(MSVC)
  # 设置 MSVC 使用 UTF-8
  add_compile_options(/utf-8)
endif()



add_library(libAutoCom STATIC com/AutoCom.h com/AutoCom.cpp)
target_include_directories(libAutoCom PUBLIC ${CMAKE_SOURCE_DIR}/com)

add_library(libTimer STATIC timer/Timer.h timer/Timer.cpp)
target_include_directories(libTimer PUBLIC ${CMAKE_SOURCE_DIR}/timer)


add_subdirectory(vtkExtension)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_CURRENT_LIST_DIR}/bin)

get_direct_subdirectories(${CMAKE_CURRENT_LIST_DIR} CHAP_DIRS)
foreach(CHAP_DIR ${CHAP_DIRS})
  get_filename_component(CHAP_DIR_NAME "${CHAP_DIR}" NAME)
  if("${CHAP_DIR_NAME}" MATCHES "Chap")
    get_direct_subdirectories(${CHAP_DIR} CHAP_CHILDREN_DIRS)
    foreach(CHAP_CHILD_DIR ${CHAP_CHILDREN_DIRS})
      if(EXISTS ${CHAP_CHILD_DIR}/CMakeLists.txt)
        get_filename_component(CHAP_CHILD_NAME ${CHAP_CHILD_DIR} NAME)
        add_subdirectory(${CHAP_DIR}/${CHAP_CHILD_NAME})
        target_link_libraries(${CHAP_CHILD_NAME} PRIVATE libAutoCom)
        target_link_libraries(${CHAP_CHILD_NAME} PRIVATE libTimer)
        target_link_libraries(${CHAP_CHILD_NAME} PRIVATE libVTKExtension)
      endif()
    endforeach()
  endif()
endforeach()

file(GLOB VTK_DLLS ${CMAKE_CURRENT_LIST_DIR}/bin/vtkCommonCore-*.dll)
if(NOT VTK_DLLS)
  get_filename_component(VTK_BIN_DIR "${VTK_DIR}/../../../bin" ABSOLUTE)
  file(COPY "${VTK_BIN_DIR}"
    DESTINATION "${CMAKE_CURRENT_LIST_DIR}/"
  )
endif()


