cmake_minimum_required(VERSION 3.15)
project(bst)
set(CMAKE_CXX_STANDARD 11)

# 搜索源文件
aux_source_directory(${PROJECT_SOURCE_DIR} SRC)
# 设置可执行程序的路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
# 生成可执行程序
add_executable(bst ${SRC})
