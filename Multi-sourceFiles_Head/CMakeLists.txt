cmake_minimum_required(VERSION 3.20)

project(Multi-sourceFiles_Head LANGUAGES CXX)

# 创建可执行文件
add_executable(Multi-sourceFiles_Head
    main.cpp
    data.cpp
    grade.cpp
    io.cpp
    sort.cpp
    sort.h io.h grade.h data.h
    coursegrade.dat
)

# 设置C++标准为C++20，支持概念和范围
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加编译特性以确保支持C++20特性
target_compile_features(Multi-sourceFiles_Head PRIVATE cxx_std_20)
