cmake_minimum_required(VERSION 3.27)
project(WhaleProject LANGUAGES CXX)

# C++
set(CMAKE_CXX_STANDARD 20)

# Compiler
if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)

    #    set(BOOST_ROOT "D:/boost_1_85_0/")    # 指定Boost库的根目录
    #    set(Boost_USE_STATIC_LIBS ON)    # 设置使用Boost静态库
    #    set(Boost_ARCHITECTURE "-x64")    # 指定库架构为x64
    #    find_package(Boost COMPONENTS regex REQUIRED)    # 查找Boost库
    #    include_directories(${Boost_INCLUDE_DIRS})    # 包含Boost库的头文件目录

elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    add_compile_options(
            /utf-8
            #            /wd4061 # 枚举的开关中的枚举器未由事例标签显式处理
            #            /wd4100 # 未引用的形参
            #            /wd4365 # 有符号/无符号不匹配
            #            /wd4514 # 未引用的内联函数已移除
            #            /wd4548 # 逗号前的表达式不起任何作用；应输入带副作用的表达式
            #            /wd4623 # 已将默认构造函数隐式定义为“已删除”
            #            /wd4625 # 已将复制构造函数隐式定义为“已删除”
            #            /wd4626 # 已将赋值运算符隐式定义为“已删除”
            #            /wd4668 # 没有将“XXX宏”定义为预处理器宏，用“0”替换“#if/#elif”
            #            /wd4710 # 函数未内联
            #            /wd4711 # 为自动内联扩展选定了函数
            #            /wd4820 # 数据成员后添加了n字节填充
            #            /wd4866 # 编译器无法针对调用强制执行从左到右求值顺序
            #            /wd5026 # 已将移动构造函数隐式定义为“已删除”
            #            /wd5027 # 已将移动赋值运算符隐式定义为“已删除”
            #            /wd5031 # #pragma warning(pop): 可能不匹配，正在弹出的警告状态已推送到其他文件
            #            /wd5045 # 如果指定了 /Qspectre 开关，编译器会插入内存负载的 Spectre 缓解
            #            /wd5204 # 类包含虚函数，但其常用的析构函数不是虚函数；从该类派生的实例可能无法进行正确析构
            #            /wd5240 # "maybe_unused": 特性在此语法位置被忽略
            #            /wd5267 # 已弃用隐式 复制构造函数 定义，因为它具有用户提供的 赋值运算符
    )
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)

else ()
    message(WARNING "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")
endif ()

# Wall
add_compile_options(-Wall)

# UNICODE
add_definitions("-DUNICODE" "-D_UNICODE")

# output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# include
include_directories(".")

# sub
add_subdirectory(GLAD)
add_subdirectory(Test)
add_subdirectory(Whale)
