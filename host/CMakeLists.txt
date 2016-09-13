cmake_minimum_required (VERSION 2.6)

project(example)

# Add constants file from firmware
file(GLOB firmware_constants_SOURCE  ${example_SOURCE_DIR}/../firmware/constants.cpp)

include_directories(${example_SOURCE_DIR}/../firmware/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs}) 
    message(STATUS "dir='${dir}'")
endforeach()

add_executable(
    example 
    ${firmware_constants_SOURCE}
    hid_LINUX.c
    rawhid_device.cpp
    controller.cpp
    main.cpp
    )

target_link_libraries(example usb)



