# CMakeList.txt : CMake project for Dargon, include source and define
# project specific logic here.
#

# Add source to this project's executable.
file(GLOB src_files "src/*.cpp")

add_executable (Dargon ${src_files})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Dargon PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
target_include_directories(Dargon PUBLIC "Headers/")
target_link_libraries(Dargon sfml-graphics sfml-window sfml-system RS232 ImGui-S)