set(target_name stm32f4xx_hal_cpp)

add_library(${target_name} INTERFACE)

target_include_directories(${target_name}
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${target_name} INTERFACE mcu)
