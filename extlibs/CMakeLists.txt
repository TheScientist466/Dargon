
set(BUILD_SHARED_LIBS false)
set(SFML_BUILD_NETWORK false)
set(SFML_BUILD_AUDIO false)
set(SFML_BUILD_GRAPHICS true)
set(SFML_BUILD_WINDOW true)
set(SFML_STATIC_LIBRARIES true)
add_subdirectory(SFML)

add_library(RS232 "RS-232/rs232.c")
target_include_directories(RS232 PUBLIC "RS-232/")