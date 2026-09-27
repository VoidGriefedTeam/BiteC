cmake_minimum_required(VERSION 4.2)

project(bitec
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ============================================================
# Paths
# ============================================================

set(ZLIB_SOURCE_DIR
    "${CMAKE_SOURCE_DIR}/THIRD_PARTY/zlib"
)

set(ZSTD_SOURCE_DIR
    "${CMAKE_SOURCE_DIR}/THIRD_PARTY/zstd"
)

set(ZLIB_BUILD_DIR
    "${CMAKE_BINARY_DIR}/zlib-build"
)

set(ZSTD_BUILD_DIR
    "${CMAKE_BINARY_DIR}/zstd-build"
)

set(ZLIB_INSTALL_DIR
    "${CMAKE_BINARY_DIR}/zlib-install"
)

set(ZSTD_INSTALL_DIR
    "${CMAKE_BINARY_DIR}/zstd-install"
)


# ============================================================
# Build zlib
# ============================================================

message(STATUS "========================================")
message(STATUS "Building zlib")
message(STATUS "========================================")

execute_process(
    COMMAND
        "${CMAKE_COMMAND}"
        -S "${ZLIB_SOURCE_DIR}"
        -B "${ZLIB_BUILD_DIR}"
        -G Ninja
        "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DCMAKE_INSTALL_PREFIX=${ZLIB_INSTALL_DIR}"
        "-DBUILD_SHARED_LIBS=OFF"
    RESULT_VARIABLE ZLIB_CONFIGURE_RESULT
)

if(NOT ZLIB_CONFIGURE_RESULT EQUAL 0)
    message(FATAL_ERROR
        "zlib configuration failed."
    )
endif()

execute_process(
    COMMAND
        "${CMAKE_COMMAND}"
        --build "${ZLIB_BUILD_DIR}"
        --config "${CMAKE_BUILD_TYPE}"
    RESULT_VARIABLE ZLIB_BUILD_RESULT
)

if(NOT ZLIB_BUILD_RESULT EQUAL 0)
    message(FATAL_ERROR
        "zlib build failed."
    )
endif()

execute_process(
    COMMAND
        "${CMAKE_COMMAND}"
        --install "${ZLIB_BUILD_DIR}"
        --config "${CMAKE_BUILD_TYPE}"
    RESULT_VARIABLE ZLIB_INSTALL_RESULT
)

if(NOT ZLIB_INSTALL_RESULT EQUAL 0)
    message(FATAL_ERROR
        "zlib installation failed."
    )
endif()

message(STATUS
    "zlib installed to: ${ZLIB_INSTALL_DIR}"
)


# ============================================================
# Find actual zlib library
# ============================================================

set(
    ZLIB_LIB_DIR
    "${ZLIB_INSTALL_DIR}/lib"
)

find_library(
    ZLIB_LIB
    NAMES
        zlib
        libz
        zd
        zsd
        libzd
        libzsd
    PATHS
        "${ZLIB_LIB_DIR}"
    NO_DEFAULT_PATH
)

if(NOT ZLIB_LIB)

    message(STATUS "Contents of zlib lib directory:")

    file(GLOB ZLIB_LIB_FILES
        "${ZLIB_LIB_DIR}/*"
    )

    foreach(LIB_FILE ${ZLIB_LIB_FILES})
        message(STATUS "  ${LIB_FILE}")
    endforeach()

    message(FATAL_ERROR
        "Could not find zlib library in:\n"
        "  ${ZLIB_LIB_DIR}"
    )

endif()

message(STATUS
    "BiteC zlib library: ${ZLIB_LIB}"
)

message(STATUS
    "BiteC zlib library: ${ZLIB_LIB}"
)


# ============================================================
# Build zstd
# ============================================================

message(STATUS "========================================")
message(STATUS "Building zstd")
message(STATUS "========================================")

execute_process(
    COMMAND
        "${CMAKE_COMMAND}"
        -S "${ZSTD_SOURCE_DIR}"
        -B "${ZSTD_BUILD_DIR}"
        -G Ninja
        "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DCMAKE_INSTALL_PREFIX=${ZSTD_INSTALL_DIR}"
        "-DZSTD_BUILD_SHARED=ON"
        "-DZSTD_BUILD_STATIC=OFF"
        "-DZSTD_BUILD_PROGRAMS=OFF"
        "-DZSTD_BUILD_TESTS=OFF"
    RESULT_VARIABLE ZSTD_CONFIGURE_RESULT
)

if(NOT ZSTD_CONFIGURE_RESULT EQUAL 0)
    message(FATAL_ERROR
        "zstd configuration failed."
    )
endif()

execute_process(
    COMMAND
        "${CMAKE_COMMAND}"
        --build "${ZSTD_BUILD_DIR}"
        --config "${CMAKE_BUILD_TYPE}"
    RESULT_VARIABLE ZSTD_BUILD_RESULT
)

if(NOT ZSTD_BUILD_RESULT EQUAL 0)
    message(FATAL_ERROR
        "zstd build failed."
    )
endif()

execute_process(
    COMMAND
        "${CMAKE_COMMAND}"
        --install "${ZSTD_BUILD_DIR}"
        --config "${CMAKE_BUILD_TYPE}"
    RESULT_VARIABLE ZSTD_INSTALL_RESULT
)

if(NOT ZSTD_INSTALL_RESULT EQUAL 0)
    message(FATAL_ERROR
        "zstd installation failed."
    )
endif()

message(STATUS
    "zstd installed to: ${ZSTD_INSTALL_DIR}"
)


# ============================================================
# Find actual zstd library
# ============================================================

set(
    ZSTD_LIB
    "${ZSTD_INSTALL_DIR}/lib/zstd.lib"
)

if(NOT EXISTS "${ZSTD_LIB}")

    message(FATAL_ERROR
        "Could not find zstd library:\n"
        "  ${ZSTD_LIB}"
    )

endif()

message(STATUS
    "BiteC zstd library: ${ZSTD_LIB}"
)


# ============================================================
# Create zlib target for LLVM
# ============================================================

if(NOT TARGET ZLIB::ZLIB)

    add_library(
        ZLIB::ZLIB
        STATIC
        IMPORTED
    )

    set_target_properties(
        ZLIB::ZLIB
        PROPERTIES

        INTERFACE_INCLUDE_DIRECTORIES
            "${ZLIB_INSTALL_DIR}/include"

        IMPORTED_LOCATION
            "${ZLIB_LIB}"

        IMPORTED_LOCATION_DEBUG
            "${ZLIB_LIB}"

        IMPORTED_LOCATION_RELEASE
            "${ZLIB_LIB}"

        IMPORTED_LOCATION_RELWITHDEBINFO
            "${ZLIB_LIB}"

        IMPORTED_LOCATION_MINSIZEREL
            "${ZLIB_LIB}"

        IMPORTED_LOCATION_NOCONFIG
            "${ZLIB_LIB}"

        IMPORTED_IMPLIB
            "${ZLIB_LIB}"

        IMPORTED_IMPLIB_DEBUG
            "${ZLIB_LIB}"

        IMPORTED_IMPLIB_RELEASE
            "${ZLIB_LIB}"

        IMPORTED_IMPLIB_RELWITHDEBINFO
            "${ZLIB_LIB}"

        IMPORTED_IMPLIB_MINSIZEREL
            "${ZLIB_LIB}"

        IMPORTED_IMPLIB_NOCONFIG
            "${ZLIB_LIB}"
    )

endif()


# ============================================================
# Create zstd target for LLVM
# ============================================================

if(NOT TARGET zstd::libzstd_static)

    add_library(
        zstd::libzstd_static
        STATIC
        IMPORTED
    )

    set_target_properties(
        zstd::libzstd_static
        PROPERTIES

        INTERFACE_INCLUDE_DIRECTORIES
            "${ZSTD_INSTALL_DIR}/include"

        IMPORTED_LOCATION
            "${ZSTD_LIB}"

        IMPORTED_LOCATION_DEBUG
            "${ZSTD_LIB}"

        IMPORTED_LOCATION_RELEASE
            "${ZSTD_LIB}"

        IMPORTED_LOCATION_RELWITHDEBINFO
            "${ZSTD_LIB}"

        IMPORTED_LOCATION_MINSIZEREL
            "${ZSTD_LIB}"

        IMPORTED_LOCATION_NOCONFIG
            "${ZSTD_LIB}"

        IMPORTED_IMPLIB
            "${ZSTD_LIB}"

        IMPORTED_IMPLIB_DEBUG
            "${ZSTD_LIB}"

        IMPORTED_IMPLIB_RELEASE
            "${ZSTD_LIB}"

        IMPORTED_IMPLIB_RELWITHDEBINFO
            "${ZSTD_LIB}"

        IMPORTED_IMPLIB_MINSIZEREL
            "${ZSTD_LIB}"

        IMPORTED_IMPLIB_NOCONFIG
            "${ZSTD_LIB}"
    )

endif()


# ============================================================
# LLVM
# ============================================================

find_package(LLVM REQUIRED CONFIG)

message(STATUS
    "Found LLVM ${LLVM_VERSION}"
)

message(STATUS
    "LLVM include directories: ${LLVM_INCLUDE_DIRS}"
)

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

    src/lexer/lexer.cpp

    src/translator/translator.cpp
    src/translator/var_create.cpp
    src/translator/var_fill.cpp
    src/translator/io.cpp

    src/compiler/object.cpp
    src/compiler/linker.cpp
    src/compiler/winlink.cpp
    src/compiler/linlink.cpp
)


# ============================================================
# MSVC
# ============================================================

if(MSVC)

    target_compile_options(
        bitec
        PRIVATE

        /utf-8
    )

endif()


# ============================================================
# Include directories
# ============================================================

target_include_directories(
    bitec
    PRIVATE

    "${CMAKE_SOURCE_DIR}/include"

    "${CMAKE_SOURCE_DIR}/THIRD_PARTY"
)

target_include_directories(
    bitec
    SYSTEM
    PRIVATE

    "${LLVM_INCLUDE_DIRS}"

    "${ZLIB_INSTALL_DIR}/include"

    "${ZSTD_INSTALL_DIR}/include"
)


# ============================================================
# LLVM components
# ============================================================

llvm_map_components_to_libnames(
    LLVM_LIBS

    Core
    Support

    AsmParser

    Target
    TargetParser

    MC
    MCParser
    MCDisassembler

    CodeGen

    X86
    AArch64
)


# ============================================================
# Link libraries
# ============================================================

target_link_libraries(
    bitec
    PRIVATE

    CompilerUtils

    ${LLVM_LIBS}
)


# ============================================================
# zstd DLL
# ============================================================

set(
    ZSTD_DLL
    "${ZSTD_INSTALL_DIR}/bin/zstd.dll"
)

if(NOT EXISTS "${ZSTD_DLL}")

    message(FATAL_ERROR
        "Could not find zstd DLL:\n"
        "  ${ZSTD_DLL}"
    )

endif()


# ============================================================
# Copy zstd.dll beside bitec.exe
# ============================================================

add_custom_command(
    TARGET bitec
    POST_BUILD

    COMMAND
        "${CMAKE_COMMAND}"
        -E copy_if_different

        "${ZSTD_DLL}"

        "$<TARGET_FILE_DIR:bitec>"
)


# ============================================================
# Copy runtime beside bitec.exe
# ============================================================

add_custom_command(
    TARGET bitec
    POST_BUILD

    COMMAND
        "${CMAKE_COMMAND}"
        -E copy_directory

        "${CMAKE_SOURCE_DIR}/runtime"

        "$<TARGET_FILE_DIR:bitec>/runtime"
)


# ============================================================
# Install BiteC
# ============================================================

install(
    TARGETS bitec
    RUNTIME DESTINATION .
)


# ============================================================
# Install zstd DLL
# ============================================================

install(
    FILES
        "${ZSTD_DLL}"

    DESTINATION .
)


# ============================================================
# Install runtime
# ============================================================

install(
    DIRECTORY
        "${CMAKE_SOURCE_DIR}/runtime/"

    DESTINATION runtime
)
