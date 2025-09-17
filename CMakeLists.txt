# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(lvgl)

# Include all C source files from src directory
file(GLOB_RECURSE app_sources 
    src/*.c
)

# Add all source files to the app target
target_sources(app PRIVATE ${app_sources})

# Include directories for headers
target_include_directories(app PRIVATE 
    src
)