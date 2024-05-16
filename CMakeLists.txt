cmake_minimum_required(VERSION 3.13)

# PICO_SDK_PATH required.
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(mcupico C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

# scan all source files in directory.
file(GLOB_RECURSE SRC_CPP "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE SRC_CC "${PROJECT_SOURCE_DIR}/src/*.c")

# merge two scan results.
set(ALL_SRCS ${SRC_CC} ${SRC_CPP})
add_library(mcupico ${ALL_SRCS})

pico_enable_stdio_usb(mcupico 0)
target_link_libraries(mcupico
    pico_stdlib
#    pico_unique_id
#    pico_bootrom
#    pico_multicore
#    pico_sync
    hardware_gpio
    hardware_spi
)

target_include_directories(mcupico
PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/include
    #$ENV{PICO_SDK_PATH}/lib/tinyusb/hw
    #$ENV{PICO_SDK_PATH}/lib/tinyusb/src
)

#pico_add_extra_outputs(mcupico)
    