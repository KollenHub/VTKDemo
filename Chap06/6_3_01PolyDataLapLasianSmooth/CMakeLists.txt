get_directory_name(EXE_NAME)

# 查找当前项目下所有的文件
file(GLOB_RECURSE SRC_FILES *.cpp *.h *.hpp)

add_executable(${EXE_NAME} ${SRC_FILES})

target_link_libraries(${EXE_NAME} PRIVATE 
 ${VTK_LIBRARIES})

# vtk_module_autoinit is needed
vtk_module_autoinit(
  TARGETS ${EXE_NAME}
  MODULES ${VTK_LIBRARIES}
)