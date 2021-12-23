# 打印信息
message(STATUS "src This is BINARY dir " ${PROJECT_BINARY_DIR})
message(STATUS "src This is SOURCE dir " ${PROJECT_SOURCE_DIR})


# 定义工程根目录; CMAKE_SOURCE_DIR为内建变量，表示工程根目录的CMakeLists.txt文件路径
SET(ROOT_DIR ${CMAKE_SOURCE_DIR})

# 是否使用自己的 Math库
option (USE_MYMATH "Use provided math implementation" ON)
# 用于测试替换用的变量
set(TEST_ON 1)
set(TEST_OF 0)
set(VAR "VAR_NEW")

# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file (
"${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
"${CMAKE_CURRENT_BINARY_DIR}/config.h"
)

set(SRC_LIST main.cpp)

# 是否编译Math函数
if (USE_MYMATH)
set(SRC_LIST main.cpp Math.cpp)
endif (USE_MYMATH)

# 指定可执行文件存放目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
# 这样可以找到config.h头文件
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# 构建可执行程序
ADD_EXECUTABLE(sample8 ${SRC_LIST})