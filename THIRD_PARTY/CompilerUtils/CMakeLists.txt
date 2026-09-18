add_library(CompilerUtils
    src/CompilerUtils.cpp
)

target_include_directories(CompilerUtils
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(CompilerUtils
    PUBLIC
        fmt::fmt
)