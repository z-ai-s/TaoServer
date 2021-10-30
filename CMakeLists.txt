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
    src/private/config.cpp
    )
#设置include搜索路径
include_directories(${PROJECT_SOURCE_DIR}/src/public)
include_directories(/usr/local/include)
#库文件搜索路径
link_directories(/usr/local/lib)
#生成动态库
add_library(tao STATIC ${LIB_SRC})
#指定生成的可执行文件和生成的动态库的保存路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
#生成可执行文件
#Logger
add_executable(testLog.bin tests/testLog.cpp)
add_dependencies(testLog.bin tao)
target_link_libraries(testLog.bin tao yaml-cpp)
#Config
add_executable(testConfig.bin tests/testConfig.cpp)
add_dependencies(testConfig.bin tao)
target_link_libraries(testConfig.bin tao yaml-cpp)


