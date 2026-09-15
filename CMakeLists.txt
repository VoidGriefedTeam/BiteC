cmake_minimum_required(VERSION 4.2)

project(bitec
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Dependency prefixes
list(APPEND CMAKE_PREFIX_PATH
    "E:/zlib-install"
    "E:/zstd-install"
    "E:/libxml2-install"
)

# Find LLVM
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_VERSION}")
message(STATUS "LLVM include directories: ${LLVM_INCLUDE_DIRS}")

# LLVM compile definitions
add_definitions(${LLVM_DEFINITIONS})

# Compiler executable
add_executable(bitec
    src/main.cpp
)

target_include_directories(bitec PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${LLVM_INCLUDE_DIRS}
)

# LLVM libraries
llvm_map_components_to_libnames(LLVM_LIBS
    Core
    Support
)

target_link_libraries(bitec PRIVATE
    ${LLVM_LIBS}
)