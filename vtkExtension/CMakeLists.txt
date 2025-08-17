cmake_minimum_required(VERSION 3.20)

project(vtkExtension)

add_library(libVTKExtension STATIC  vtkAxisHelper.cxx vtkAxisHelper.h)
target_link_libraries(libVTKExtension PUBLIC ${VTK_LIBRARIES})
target_include_directories(libVTKExtension PUBLIC ${CMAKE_CURRENT_LIST_DIR})

