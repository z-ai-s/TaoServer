#工程参数
cmake_minimum_required(VERSION 3.0)
project(Tao)
#编译参数
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -g -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")
#设置变量
set(LIB_SRC
    src/private/log.cpp
    src/private/util.cpp
    )
#设置include搜索路径
include_directories(${PROJECT_SOURCE_DIR}/src/public)
#生成动态库
add_library(src SHARED ${LIB_SRC})
#生成可执行文件
add_executable(test.bin tests/test.cpp)
add_dependencies(test.bin src)
target_link_libraries(test.bin src)
#指定生成的可执行文件和生成的动态库的保存路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
