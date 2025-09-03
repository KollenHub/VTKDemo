get_directory_name(EXE_NAME)

# 查找当前项目下所有的文件
file(GLOB_RECURSE SRC_FILES *.cpp *.h *.hpp *.ui *.qrc)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


add_executable(${EXE_NAME} ${SRC_FILES})

target_link_libraries(${EXE_NAME} PRIVATE
  ${VTK_LIBRARIES} Qt5::Widgets Qt5::Core Qt5::Gui)

# vtk_module_autoinit is needed
vtk_module_autoinit(
  TARGETS ${EXE_NAME}
  MODULES ${VTK_LIBRARIES}
)

message("TARGET ${EXE_NAME} POST_BUILD
  COMMAND ${WindeployqtPATH} $<TARGET_FILE:${EXE_NAME}>")
add_custom_command(TARGET ${EXE_NAME} POST_BUILD
  COMMAND ${WindeployqtPATH} $<TARGET_FILE:${EXE_NAME}>)
