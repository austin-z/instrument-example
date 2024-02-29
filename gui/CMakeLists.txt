cmake_minimum_required(VERSION 3.10)
project(scissors_example_gui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)

include_directories(${CMAKE_SOURCE_DIR}/sdk/include)

set(SOURCES
    main.cpp
    widget.cpp
)

set(HEADERS
    widget.h
)

# qt5_add_resources(RESOURCES resources.qrc)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)

# Link pthread library
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/sdk/libinstruments.so)

# Set output directory for the shared library
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)