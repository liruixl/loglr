# CMake 最低版本号要求
# cmake .. -G "MinGW Makefiles"
cmake_minimum_required (VERSION 3.2)

# 项目信息
project (loglr)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
# CMake 会将当前目录所有源文件的文件名赋值给变量 DIR_SRCS 
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable(${PROJECT_NAME} ${DIR_SRCS})