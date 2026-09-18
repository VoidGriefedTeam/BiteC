cmake_minimum_required(VERSION 4.2)

project(bitec
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# ============================================================
# Dependency prefixes
# ============================================================

list(APPEND CMAKE_PREFIX_PATH
    "E:/zlib-install"
    "E:/libxml2-install"
    "E:/zstd-install"
)


# ============================================================
# LLVM
# ============================================================

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_VERSION}")
message(STATUS "LLVM include directories: ${LLVM_INCLUDE_DIRS}")

add_definitions(${LLVM_DEFINITIONS})


# ============================================================
# fmt
# ============================================================

add_subdirectory(
    "${CMAKE_SOURCE_DIR}/THIRD_PARTY/fmt"
    "${CMAKE_BINARY_DIR}/fmt"
    EXCLUDE_FROM_ALL
)


# ============================================================
# CompilerUtils
# ============================================================

add_subdirectory(
    "${CMAKE_SOURCE_DIR}/THIRD_PARTY/CompilerUtils"
)


# ============================================================
# BiteC executable
# ============================================================

add_executable(bitec
    src/main.cpp
    src/lexer.cpp
    src/translator.cpp
)


# ============================================================
# MSVC
# ============================================================

if(MSVC)
    target_compile_options(bitec PRIVATE
        /utf-8
    )
endif()


# ============================================================
# Include directories
# ============================================================

target_include_directories(bitec PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${LLVM_INCLUDE_DIRS}"
    "${CMAKE_SOURCE_DIR}/THIRD_PARTY"
)


# ============================================================
# LLVM libraries
# ============================================================

llvm_map_components_to_libnames(LLVM_LIBS
    Core
    Support
)


# ============================================================
# Linking
# ============================================================

target_link_libraries(bitec PRIVATE
    CompilerUtils
    ${LLVM_LIBS}
)