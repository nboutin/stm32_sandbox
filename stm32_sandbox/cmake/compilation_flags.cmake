
set(flags "-Wall -Werror -Wextra -Wpedantic -Wconversion -Wcast-align -Wunused -Wshadow")
string(APPEND flags " -funsigned-char -fshort-enums -fshort-wchar")
string(APPEND flags " -Wpointer-arith -Wcast-qual -Wno-missing-braces")


# fixme: delete this
string(APPEND flags " -Wno-missing-field-initializers")

# --- C

string(APPEND CMAKE_C_FLAGS " ${flags}  -Wmissing-prototypes")
string(APPEND CMAKE_C_FLAGS " -Wno-missing-prototypes") # fixme: disable this

# --- C++

string(APPEND CMAKE_CXX_FLAGS " ${flags} ${cxx_flags}")
# set(cxx_flags "-Wold-style-cast") # fixme: enable this
