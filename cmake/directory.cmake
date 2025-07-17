function(get_direct_subdirectories base_dir result_var)
    # 获取当前目录中的所有文件或文件夹
    file(GLOB entries RELATIVE ${base_dir} ${base_dir}/*)

    set(subdirectories "")

    foreach(entry ${entries})
        if(IS_DIRECTORY "${base_dir}/${entry}")
            list(APPEND subdirectories "${base_dir}/${entry}")
        endif()
    endforeach()

    # 返回直接子文件夹
    set(${result_var} ${subdirectories} PARENT_SCOPE)
endfunction()

# 定义一个函数获取当前或父目录名称
# 用法:
#   get_directory_name(<OUT_VAR> [PARENT])
# 参数:
#   OUT_VAR - 输出变量名，用于存储目录名称
#   PARENT  - 可选，如果指定则获取父目录名称
function(get_directory_name OUT_VAR)
    # 解析参数
    set(options PARENT)
    cmake_parse_arguments(ARG "${options}" "" "" ${ARGN})

    # 获取当前目录绝对路径
    get_filename_component(CURRENT_DIR_ABS ${CMAKE_CURRENT_LIST_DIR} ABSOLUTE)

    if(ARG_PARENT)
        # 获取父目录名称
        get_filename_component(PARENT_DIR ${CURRENT_DIR_ABS} DIRECTORY)
        get_filename_component(PARENT_DIR_NAME ${PARENT_DIR} NAME)
        set(${OUT_VAR} ${PARENT_DIR_NAME} PARENT_SCOPE)
    else()
        # 获取当前目录名称
        get_filename_component(CURRENT_DIR_NAME ${CURRENT_DIR_ABS} NAME)
        set(${OUT_VAR} ${CURRENT_DIR_NAME} PARENT_SCOPE)
    endif()
endfunction()