cmake_minimum_required(VERSION 3.0.0)
project(ex01 VERSION 0.1.0)

include(CTest)
enable_testing()

set(C_STANDARD 99)
add_compile_options(-Wall -Wextra -pedantic -Werror)
add_library(ex01 SHARED Matrix.c ErrorCode.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
