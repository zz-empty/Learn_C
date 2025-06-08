cmake_minimum_required(VERSION 3.15)
project(bst)
set(CMAKE_CXX_STANDARD 11)

# 搜索源文件
aux_source_directory(${PROJECT_SOURCE_DIR} SRC)
# 设置可执行程序的路径
set(HOME /home/bbb/learning/Repo_c/c_bst/)
set(EXECUTABLE_OUTPUT_PATH ${HOME}/bin)
# 生成可执行程序
add_executable(bst ${SRC})
