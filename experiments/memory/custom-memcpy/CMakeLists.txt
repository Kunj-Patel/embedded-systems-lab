# 1. every CMake file needs a minimum version number.
cmake_minimum_required(VERSION 3.10)

# 2. name the project and specify the programming language.
project(custom_memcpy C)

# 3. add compiler flags. -O0 is used to disable optimizations.
add_compile_options(-O0)

# 4. Tell CMake we want to build an executable program called 'memcpy_bench'.
# The files listed after it are the source files it needs to compile.
add_executable(memcpy_bench main.c custom_string.c)

