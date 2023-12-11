
set(target_name board)

add_library(${target_name} INTERFACE)

target_include_directories(${target_name} INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${target_name} INTERFACE
    stm32f4xx_hal_cpp
)
