
set(target_name mcu)

add_library(${target_name} INTERFACE)

target_include_directories(${target_name} INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
