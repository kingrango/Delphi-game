cmake_minimum_required(VERSION 3.16)
project(AdbDeviceManager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt6_standard_project_setup()

set(SOURCES
    main.cpp
    mainwindow.cpp
)

set(HEADERS
    mainwindow.h
)

qt6_add_executable(AdbDeviceManager ${SOURCES} ${HEADERS})

target_link_libraries(AdbDeviceManager Qt6::Core Qt6::Widgets)

# Create data directory for APK files
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/data)

# Copy data directory to build output
add_custom_command(TARGET AdbDeviceManager POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data
    COMMENT "Copying data directory to build output"
)