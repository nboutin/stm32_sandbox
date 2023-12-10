
# add_custom_command(TARGET ${target_name} POST_BUILD
#   COMMENT "Compute binary size"
#   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#   COMMAND ${CMAKE_SIZE_UTIL} -G -x ${target_name}.elf
#   # COMMAND ${CMAKE_SIZE_UTIL} -A -x ${target_name}.elf
# )

string(APPEND CMAKE_EXE_LINKER_FLAGS " -Wl,--print-memory-usage")
