cmake_minimum_required(VERSION 3.10)
project(scissors_example_cli)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add source files
file(GLOB_RECURSE SOURCES main.cpp)

# Add header files path if needed
include_directories(${CMAKE_SOURCE_DIR}/sdk/include)

# Add executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Link pthread library
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/sdk/libinstruments.so)

# Set output directory for the shared library
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Optionally, install the library
#install(TARGETS scissors_example LIBRARY DESTINATION lib)

# Optionally, install headers
#install(DIRECTORY include/ DESTINATION include)